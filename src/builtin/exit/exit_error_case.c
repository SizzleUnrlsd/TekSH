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
exit_error_extend(shell_t *shell, char **arg,
                    int32_t count, int32_t expected_value)
{
    if (count == _strlen(arg[1]) && count > 0) {
        expected_value = _get_nbr(arg[1]);
        ENDING_PROCESS_("exit", expected_value)
    } else if (count > 0 && (arg[1][0] > 47 && arg[1][0] < 58)) {
        EXIT_W_ECHO_ERROR_("exit: Badly formed number.", 1);
    }
    return 0;
}

int32_t
exit_error(shell_t *shell, char **arg, int32_t len_arg)
{
    if (len_arg == 2) {
        int32_t count = 0;
        int32_t expected_value = 0;
        for (int32_t i = 0; arg[1][i]; i++)
            (arg[1][i] > 47 && arg[1][i] < 58 ? count++ : 0);
        if (exit_error_extend(shell, arg, count, expected_value) == 1)
            return 1;
    }
    if (len_arg == 2 && _strlen(arg[1]) != 1 && arg[1][0] == '-') {
        ENDING_PROCESS_("exit", 255);
    }
    if (len_arg != 1) {
        EXIT_W_ECHO_ERROR_("exit: Expression Syntax.", 1);
    } else if (len_arg == 1) {
        ENDING_PROCESS_("exit", 0)
    }
    return 0;
}
