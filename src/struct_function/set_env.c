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
retrieve_env(shell_t *shell, char **env)
{
    uint32_t full_size = len_array(env) + 1;

    if ((full_size - 1) == 0) {
        char *env_null[] =
        {"HOSTTYPE=x86_64-linux", "VENDOR=unknown", "OSTYPE=linux",
        "MACHTYPE=x86_64", "SHLVL=1", "PWD=/home/hugo/test_compilation/B-PSU-200-RUN-2-1-42sh-hugo.payet", NULL};
        
        shell->set_env = (set_env_t*)malloc_attribut(sizeof(set_env_t), shell);
        shell->set_env->env_array = (char**)malloc_attribut(sizeof(char *) * 7, shell);
        memcpy(shell->set_env->env_array, env_null, 7 * sizeof(char *));
        shell->set_env->env_array[7 - 1] = NULL;
        return;
    } else {
        shell->set_env = (set_env_t*)malloc_attribut(sizeof(set_env_t), shell);
        shell->set_env->env_array = (char**)malloc_attribut(sizeof(char *) * full_size, shell);
        memcpy(shell->set_env->env_array, env, full_size * sizeof(char *));
        shell->set_env->env_array[full_size - 1] = NULL;
        return;
    }
}
