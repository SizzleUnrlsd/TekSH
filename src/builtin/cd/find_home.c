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

static char *
_strdup_bool(char const *src,  shell_t *shell, bool stat)
{
    int32_t a = 0;
    char *dest = NULL;

    if (stat == true)
        dest = (char*)malloc_attribut
        (sizeof(char) * (_strlen(src) + 1), shell);
    else
        dest = malloc(sizeof(char) * (_strlen(src) + 1));

    while (src[a] != '\0') {
        dest[a] = src[a];
        a++;
    }
    dest[a] = '\0';
    return (dest);
}

char *
find_home(shell_t *shell, char *home)
{
    char **first_step = NULL;
    char **env = shell->set_env->env_array;

    for (int32_t i = 0; env[i]; i++) {
        first_step = _str_to_word_array_custom(shell, env[i], '=');
        if (_strcmp(first_step[0], "HOME") == 0) {
            home = _strdup_bool(first_step[1], shell, true);
            return home;
        }
    }
    return NULL;
}
