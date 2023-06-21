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
is_builtin(shell_t *shell, char *cmd)
{
    if (cmd == NULL)
        return -1;
    cmd++;
    char **arg = parse_stdin(_strdup(cmd, shell), shell);
    int32_t len_arg = len_array(arg);

    if (strncmp(cmd, "setenv", 6) == 0 && len_arg == 1)
        return 1;
    if (strncmp(cmd, "setenv", 6) == 0 && len_arg != 1)
        return 2;

    if (strncmp(cmd, "env", 3) == 0 ||
        strncmp(cmd, "exit", 4) == 0) {
        return 1;
    }
    if (strncmp(cmd, "cd", 2) == 0 || strncmp(cmd, "unsetenv", 8) == 0) {
        return 2;
    }
    return -1;
}
