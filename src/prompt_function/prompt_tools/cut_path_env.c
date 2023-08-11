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

#include "shell.h"

char **cut_path_env(char **array)
{
    char **path = DEFAULT(path);
    char **full_env = DEFAULT(full_env);
    int32_t integer_path = DEFAULT(integer_path);
    int32_t len_arr = len_array(array);

    if (len_arr == 0) {
        return NULL;
    }

    for (uint32_t i = 0; array[i] != NULL; i++) {
        full_env = _str_to_word_array_custom(array[i], '=');
        if (_strcmp(full_env[0], "PATH") == 0) {
            integer_path = 1;
            break;
        }
        // free_specific(shell, full_env);
    }
    if (integer_path == 0)
        return full_env;
    path = _str_to_word_array_custom(full_env[1], ':');
    full_env = NULL;
    return path;
}
