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

bultin_list_t builtin_list[] = {
    {"echo", &_echo},
    {"set", &my_set},
    {"cd", &builtin_cd},
    {"unset", &my_unset},
    {"env", &builtin_env},
    {"exit", &builtin_exit},
    {"!", &builtin_exclamation},
    {"setenv", &builtin_setenv},
    {"history", &builtin_history},
    {"unsetenv", &builtin_unsetenv},
    {"alias", &alias_engine},
    {"clear", &clear_term},
    {0, NULL},
};

int32_t
builtin(shell_t *shell, char **path, uint32_t *no_command)
{
    if (!path[0]) {
        return 1;
    }
    if (path[0][0] == 0) {
        shell->built_nothing++;
        (*no_command) = 3;
        return 0;
    } else {
        (*no_command) = 0;
    }
    for (int32_t i = 0; builtin_list[i].index; i++) {
        if (_strcmp(path[0], builtin_list[i].index) == 0) {
            builtin_list[i].function(shell);
            break;
        }
    }
    return 0;
}
