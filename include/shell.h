/**
 * Copyright (C) 2023 hugo
 * 
 * This file is part of TekSH.
 * 
 * TekSH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TekSH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TekSH.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SHELL_H_
    #define SHELL_H_
    #include "struct.h"
    #include "struct_define.h"
    #include "glibc.h"
    #include "ast.h"
    #include "bultin_list.h"
    #include "basic_function.h"
    #include "garbage-collector.h"
    #include "bucket.h"
    #include "alias.h"
    #include "plugin.h"
    #include "wildcard.h"
    #include "set_unset.h"

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

#ifndef _UNUSED_
#define _UNUSED_
    #define UNUSED_ARG __attribute__((unused))

#endif

#define START_FIRST __attribute__((constructor(1000)))
#define _VOID __attribute__((noreturn))
#define _wur __attribute__((__warn_unused_result__))

#ifndef JOB_CONTROL_
    #define JOB_CONTROL_
    extern uint32_t job_control;
    extern uint32_t supposed_job_control;

#endif

#ifndef CURRENT_PROCESS_
    #define CURRENT_PROCESS_
    extern bool current_process;

#endif

#ifndef GLOBAL_PROMPT_
    #define GLOBAL_PROMPT_
    extern char _gbuf[256];
    extern uint64_t count_readline;

#endif

#ifndef GLOBAL_STRUCT_SHELL_
    #define GLOBAL_STRUCT_SHELL_
    extern shell_t *_gshell;    

#endif


#ifndef VERBOSE_GLOBAL_
    #define VERBOSE_GLOBAL_
    extern bool verbosity;

#endif

#ifndef NOEFFECT_GLOBAL_
    #define NOEFFECT_GLOBAL_
    extern bool noeffect;

#endif


#ifndef COMMAND_FOUND
    #define COMMAND_FOUND           \
    shell->command_not_found++;     \
    shell->built_shell_type_env++;

#endif

#ifndef ERROR_MESSAGE_
    #define ERROR_MESSAGE_
    #define SWITCH_ERROR_(mode, var2, var3)         \
    if (mode == 0) print_str(var2, '\n', RD_TTY, 2);

#endif

#ifndef RETURN_VALUE_NO_VOID_
    #define RETURN_VALUE_NO_VOID_
    #define EXIT_W_ECHO_ERROR_(str, return_value)   \
    if (return_value == 1 && RD_TTY == 1) {         \
        print_str(str, '\n', true, 2);              \
        shell->status = return_value;               \
        return return_value;                        \
    }                                               \
    if (return_value == 1 && RD_TTY == 0) {         \
        print_str(str, '\n', true, 2);              \
        shell->status = return_value;               \
        exit(return_value);                         \
    }

#endif

#ifndef EXPECTED_EXIT_
    #define EXPECTED_EXIT_
    #define ENDING_PROCESS_(const_char, int_expected) \
    print_str(const_char, '\n', RD_TTY, 1);           \
    exit(int_expected);                               \

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
        _BUF_ERROR           = 1,
        _READ_ERROR          = 2,
        _FORK_ERROR          = 3,
        _FILE_ERROR          = 4,
        _WRITE_ERROR         = 5,
        _CONST_BUF_ERROR     = 6,
        _MEM_ALLOCA_ERROR    = 7,
        _THREAD_ALLOCA_ERROR = 8,
        _PIPE_ERROR          = 9,
        _OVERLAPPING_ERROR   = 10,
        _OPEN_ERROR          = 11,
    };

#endif

#ifndef TERMS_CAP_
    #define TERMS_CAP_
    #define _CLEAR_TERM      "\033c"
    #define ANSI_COLOR_RED   "\x1b[31m"
    #define ANSI_COLOR_BLUE  "\x1b[34m"
    #define ANSI_COLOR_RESET "\x1b[0m"
    #define ANSI_BOLD_ON     "\x1b[1m"

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
    #define _p_error(error)                             \
        do {                                            \
            char *_str;                                 \
            switch(error) {                             \
                case _BUF_ERROR:                        \
                    _str = "Buffer Error";              \
                    break;                              \
                case _FORK_ERROR:                       \
                    _str = "Fork Error";                \
                    break;                              \
                case _FILE_ERROR:                       \
                    _str = "File Error";                \
                    break;                              \
                case _WRITE_ERROR:                      \
                    _str = "Write Error";               \
                    break;                              \
                case _READ_ERROR:                       \
                    _str = "Write Read";                \
                    break;                              \
                case _CONST_BUF_ERROR:                  \
                    _str = "Constant Buffer Error";     \
                    break;                              \
                case _MEM_ALLOCA_ERROR:                 \
                    _str = "Memory Allocation Error";   \
                    break;                              \
                case _THREAD_ALLOCA_ERROR:              \
                    _str = "Thread Allocation Error";   \
                    break;                              \
                case _PIPE_ERROR:                       \
                    _str = "Pipe Error";                \
                    break;                              \
                case _OVERLAPPING_ERROR:                \
                    _str = "Overlapping Error";         \
                    break;                              \
                case _OPEN_ERROR:                       \
                    _str = "Open error";                \
                    break;                              \
                default:                                \
                    _str = "Unknown Error";             \
                    break;                              \
            }                                           \
            print_str(_str, 0, true, STDERR_FILENO);    \
        } while(0)
#endif

#ifndef GLOBAL_BUFFER_SHELL_THEME_H
    #define GLOBAL_BUFFER_SHELL_THEME_H

    extern char _buff_shell_theme[1024];
#endif

#ifndef _DEFAULT_VAR_
    #define _DEFAULT_VAR_
    #define DEFAULT(x) _Generic((x),    \
    int32_t:  0,                        \
    uint32_t: 0,                        \
    float: 0.0f,                        \
    double: 0.0,                        \
    char:  '\0',                        \
    unsigned char:    0,                \
    size_t:   (size_t)0,                \
    ssize_t: (ssize_t)0,                \
    void*: NULL,                        \
    default: NULL)

#endif

#ifndef _RESET_VAR_
    #define _RESET_VAR_
    #define RESET(x) _Generic((x),      \
    int32_t:  0,                        \
    uint32_t: 0,                        \
    float: 0.0f,                        \
    double: 0.0,                        \
    char:  '\0',                        \
    unsigned char:    0,                \
    size_t:   (size_t)0,                \
    ssize_t: (ssize_t)0,                \
    void*: NULL,                        \
    default: NULL)

#endif

#ifndef _INIT_VAR_
    #define _INITI_VAR_
    #define INIT(x) _Generic((x),               \
        char[sizeof(x)]: (void)INIT_ARRAY(x),   \
        default: memset(&(x), 0, sizeof(x)))

#endif

#endif /* SHELL_H_ */
