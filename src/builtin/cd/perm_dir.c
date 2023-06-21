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

int32_t check_perm_dir(shell_t *shell, char *path, uint32_t *invalid_cd)
{
    if (path == NULL) {
        (*invalid_cd) = 1;
        EXIT_W_ECHO_ERROR_(": No such file or directory.", 1);
    }
    if (access(path, F_OK) != 0) {
        (*invalid_cd) = 1;
        print_str(path, 0, true, 2);
        EXIT_W_ECHO_ERROR_(": No such file or directory.", 1);
    }
    if (access(path, R_OK) != 0 && access(path, X_OK) != 0) {
        (*invalid_cd) = 1;
        print_str(path, 0, true, 2);
        EXIT_W_ECHO_ERROR_(": Permission denied.", 1);
        return 1;
    }
    return 0;
}
