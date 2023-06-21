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
#include "../../../include/set_unset.h"

int32_t
check_char_num(char c)
{
    if (c < '0' || c > '9')
        return 1;
    return 0;
}

int32_t
check_malloc(char **new_env, char *n_key)
{
    if (new_env == NULL) {
        perror("Error allocating memory");
        free(n_key);
        return 84;
    }
    return 0;
}

int32_t
check_set(shell_t *shell, char *name)
{
    if (!char_isalnum(name[0]) && name[0] != '_') {
        EXIT_W_ECHO_ERROR_("set: Variable name must begin with a letter.", 1);
        return (EXIT_FAILURE);
    }
    if (check_char_num(name[0]) == 0) {
        EXIT_W_ECHO_ERROR_("set: Variable name must begin with a letter.", 1);
        return (EXIT_FAILURE);
    }
    for (int i = 0; name[i] != '\0'; i++) {
        if (!char_isalnum(name[i]) && name[i] != '_') {
            EXIT_W_ECHO_ERROR_("set: Variable name must \
            containalphanumeric characters.", 1);
            return (EXIT_FAILURE);
        }
    }
    return 0;
}
