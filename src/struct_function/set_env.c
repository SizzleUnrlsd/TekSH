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

void
init_env(shell_t *shell, char **env)
{
    uint32_t full_size = len_array(env) + 1;

    if ((full_size - 1) == 0) {
        char *env_null[] =
        {"HOSTTYPE=", "VENDOR=", "OSTYPE=",
        "MACHTYPE=", "SHLVL=1", "PWD=", NULL};
        
        shell->set_env = (set_env_t*)_mallocbucket(sizeof(set_env_t));
        shell->set_env->env_array = (char**)_mallocbucket(sizeof(char *) * 7);
        memcpy(shell->set_env->env_array, env_null, 7 * sizeof(char *));
        shell->set_env->env_array[7 - 1] = NULL;
        return;
    } else {
        shell->set_env = (set_env_t*)_mallocbucket(sizeof(set_env_t));
        shell->set_env->env_array = (char**)_mallocbucket(sizeof(char *) * full_size);
        memcpy(shell->set_env->env_array, env, full_size * sizeof(char *));
        shell->set_env->env_array[full_size - 1] = NULL;
        return;
    }
}
