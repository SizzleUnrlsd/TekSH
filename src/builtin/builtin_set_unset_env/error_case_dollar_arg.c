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

#include "shell.h"

int32_t
error_case_dollar_arg_extend_plus
(shell_t *shell, char **arg, int32_t i, int32_t e)
{
    if ((arg[e][i] > 32 && arg[e][i] < 47)
    || (arg[e][i] > 57 && arg[e][i] < 61)
    || (arg[e][i] > 61 && arg[e][i] < 65)
    || (arg[e][i] > 90 && arg[e][i] < 95)) {
        EXIT_W_ECHO_ERROR_(ERROR_SETENV_LAST_DOLLAR, 1);
    }
    return 0;
}

int32_t
error_case_dollar_arg_extend_s
(shell_t *shell, char **arg, int32_t i, int32_t e)
{
    int32_t len_str_arg = _strlen(arg[e]) - 1;
    if (char_isalpha(arg[e][len_str_arg]) == 0 &&
        char_isdigit(arg[e][len_str_arg]) == 0
        && arg[e][len_str_arg] != '_' && arg[e][len_str_arg] != '/') {
        EXIT_W_ECHO_ERROR_(ERROR_SETENV_LAST_DOLLAR, 1);
    }
    if (arg[e][i] == '$') {
        for (; arg[e][i]; i++)
            _putchar(arg[e][i + 1], 2);
        EXIT_W_ECHO_ERROR_(ERROR_SET_UNSET_DOLLAR, 1);
    }
    if (arg[1][i] == '=') {
        EXIT_W_ECHO_ERROR_(ERROR_SETENV_LAST_DOLLAR, 1);
    }
    error_case_dollar_arg_extend_plus(shell, arg, i, e);
    return 0;
}

int32_t
error_case_no_str_is_alpha_extend(shell_t *shell, char **arg,
                                    int32_t e, int32_t pass)
{
    for (int32_t i = 0; arg[e][i]; i++) {
        (error_case_dollar_arg_extend_s(shell, arg, i, e) == 1 ?
        pass = 1 : 0);
        if (pass == 1)
            break;
    }
    if (pass == 1)
        return 1;
    return 0;
}

int32_t
error_case_no_str_is_alpha(shell_t *shell, int32_t len_arg)
{
    int32_t pass = 0; char **arg = parse_stdin(shell->get_line, shell);
    if (_strcmp(arg[0], "unsetenv") == 0)
        return 0;
    if (arg[1][0] == '\'') {
        EXIT_W_ECHO_ERROR_("Unmatched '''.", 1);
    }

    if (char_isalpha(arg[1][0]) == 0) {
        if (_strcmp(arg[0], "setenv") == 0
        && len_arg != 2 && arg[1][0] != '_') {
            EXIT_W_ECHO_ERROR_(ERROR_SETENV_FIRST_DOLLAR, 1)
        }
        if (_strcmp(arg[0], "setenv") == 0
        && len_arg > 1 && arg[1][0] != '$' && arg[1][0] != '_') {
            EXIT_W_ECHO_ERROR_(ERROR_SETENV_FIRST_DOLLAR, 1)
        }
    }
    for (int32_t e = 1; e != len_arg; e++)
        if (error_case_no_str_is_alpha_extend(shell, arg, e, pass) == 1)
            return 1;

    return 0;
}
