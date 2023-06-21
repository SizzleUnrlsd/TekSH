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

void free_wh_garbage(char **full_env)
{
    for (uint32_t i = 0; full_env[i]; i++) {
        free(full_env[i]);
        full_env[i] = NULL;
    }
    free(full_env);

    return;
}

void free_w_garbage(shell_t *shell, char **path)
{
    for (uint32_t i = 0; path[i]; i++)
        garbage_collector(path[i], shell);
    garbage_collector(path, shell);
    return;
}

void free_specific(shell_t *shell, char **full_env)
{
    for (uint32_t i = 0; full_env[i]; i++) {
        free_attribut(full_env[i], shell);
        full_env[i] = NULL;
    }
    free_attribut(full_env, shell);
}

char **cut_path_env(shell_t *shell, char **array)
{
    char **path = NULL;
    char **full_env = NULL;
    int32_t len_arr = len_array(array);
    if (len_arr == 0)
        return NULL;
    int32_t integer_path = 0;
    for (uint32_t i = 0; array[i] != NULL; i++) {
        full_env = _str_to_word_array_custom(shell, array[i], '=');
        if (_strcmp(full_env[0], "PATH") == 0) {
            integer_path = 1;
            break;
        }
        free_specific(shell, full_env);
    }
    if (integer_path == 0)
        return full_env;
    path = _str_to_word_array_custom(shell, full_env[1], ':');
    full_env = NULL;
    return path;
}
