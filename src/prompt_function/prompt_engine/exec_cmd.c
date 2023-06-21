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
execute_command(char **arg, shell_t *shell)
{
    uint32_t no_command = 0;
    if (!arg[0]) {
        return;
    }
    loader(shell, arg);
    builtin(shell, arg, &no_command);
    if (BUILT_INT_EXIT != 0) {
        exit(0);
    }
    if (SHELL_ENV == 0 && no_command == 0 && BINARY == 0) {
        prompt_function(shell, shell->set_env, arg);
    }
}
