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

void
builtin_setenv_ext(shell_t *shell, int32_t len_arg,
                int32_t in_env, int32_t mode_builtin)
{
    int32_t count = 0;
    for (int32_t i = 0; i != len_arg; i++)
        if (shell->several_arg_builtin[i] == -1)
            count++;

    if (mode_builtin == 0)
        if (count == len_array(parse_stdin(shell->get_line, shell)) - 1)
            in_env = -3;
    if (mode_builtin == 1)
        if (count == len_array(parse_stdin(shell->get_line, shell)))
            in_env = -3;
    add_line_to_array(shell, len_arg, in_env);
    return;
}
