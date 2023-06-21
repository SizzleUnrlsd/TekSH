/**
* {{ project }}
* Copyright (C) {{ year }}  {{ organization }}
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SHELL_H_
    #define SHELL_H_
    #include "struct.h"
    #include "struct_define.h"
    #include "glibc.h"
    #include "ast.h"
    #include "bultin_list.h"
    #include "basic_function.h"
    #include "garbage_collector.h"
    #include "bucket.h"
    #include "alias.h"
    #include "wildcard.h"
    #include "set_unset.h"
    #include "plugin.h"

#endif /* SHELL_H_ */

#ifdef __x86_64__
    #define ARCH "_x86_64"
#elif __i386__
    #define ARCH "_i386"
#elif __arm__
    #define ARCH "_xarm"
#elif __aarch64__
    #define ARCH "_aarch64"
#else
    #define ARCH "_ERROR"
#endif

#ifndef COMMAND_FOUND
    #define COMMAND_FOUND \
    shell->command_not_found++;  \
    shell->built_shell_type_env++;

#endif

#ifndef ERROR_MESSAGE_
    #define ERROR_MESSAGE_
    #define SWITCH_ERROR_(mode, var2, var3)\
    if (mode == 0) print_str(var2, '\n', RD_TTY, 2);

#endif

#ifndef RETURN_VALUE_NO_VOID_
    #define RETURN_VALUE_NO_VOID_
    #define EXIT_W_ECHO_ERROR_(str, return_value)\
    if (return_value == 1 && RD_TTY == 1) { \
        print_str(str, '\n', true, 2); \
        shell->status = return_value; \
        return return_value; \
    } \
    if (return_value == 1 && RD_TTY == 0) { \
        print_str(str, '\n', true, 2); \
        shell->status = return_value; \
        exit_shell(shell); \
        exit(return_value); \
    }

#endif

#ifndef EXPECTED_EXIT_
    #define EXPECTED_EXIT_
    #define ENDING_PROCESS_(const_char, int_expected) \
    print_str(const_char, '\n', RD_TTY, 1); \
    exit_shell(shell); \
    exit(int_expected); \

#endif

#ifndef UPDATE_SUCCESS_STATUS_SHELL_
    #define UPDATE_SUCCESS_STATUS_SHELL_
    #define UPDATE_SUCCESS_STATUS shell->status = 0;

#endif

#ifndef UPDATE_FAILURE_STATUS_SHELL_
    #define UPDATE_FAILURE_STATUS_SHELL_
    #define UPDATE_FAILURE_STATUS shell->status = 1;

#endif

#ifndef ERROR_TYPE_VALUE_
    #define ERROR_TYPE_VALUE_
    enum _error_code {
        _BUF_ERROR = 2,
        _FORK_ERROR = 3,
        _FILE_ERROR = 4,
        _WRITE_ERROR = 5,
        _CONST_BUF_ERROR = 6,
        _MEM_ALLOCA_ERROR = 7,
        _THREAD_ALLOCA_ERROR = 8,
    };

#endif

#ifndef TERMS_CAP_
    #define TERMS_CAP_
    #define _CLEAR_TERM "\033c"
    #define ANSI_COLOR_RED "\x1b[31m"
    #define ANSI_COLOR_BLUE "\x1b[34m"
    #define ANSI_COLOR_RESET "\x1b[0m"
    #define ANSI_BOLD_ON "\x1b[1m"

#endif

#ifndef PRINTLINE_
    #define _printline(str) print_str(str, '\n', true, 1);
#endif

#ifndef PRINT_
    #define _print(str) print_str(str, 0, true, 1);
#endif

#ifndef PRINT_F_
    #define _printf(format, ...) pfflush_wrapper(1, format, __VA_ARGS__)
#endif

#ifndef PRINT_F_ERROR_
    #define _printfe(format, ...) pfflush_wrapper(STDERR_FILENO, format, __VA_ARGS__)
#endif

#ifndef P_ERROR_
    #define _p_error(fd, str) print_str(str, 0, true, fd);
#endif

#ifndef GLOBAL_BUFFER_SHELL_THEME_H
    #define GLOBAL_BUFFER_SHELL_THEME_H

    extern char _buff_shell_theme[1024];

#endif
