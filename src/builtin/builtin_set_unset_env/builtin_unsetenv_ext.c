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

include "shell.h"

int32_t
unset_env(shell_t *shell, int32_t in_env UNUSED_ARG, int32_t *a, int32_t index)
{
    int32_t i = 0, j = 0;
    char **env = shell->set_env->env_array;
    for (; i < len_array(env); i++) {
        if (a[index] == -1) {
            return 1;
        }
        if (_strcmp(env[i], env[a[index]]) != 0)
            env[j++] = env[i];
    }
    env[j] = NULL;
    return 0;
}

int32_t
builtin_unsetenv_loop
(shell_t *shell, int32_t *a, int32_t in_env, int32_t len_arg)
{
    for (int32_t e = 0; e != len_arg - 1; e++) {
        if (unset_env(shell, in_env, a, e) == 1)
            continue;
        for (int32_t i = 0; i != len_arg; i++)
            a[i] = a[i] - 1;
    }
    return 0;
}

void
builtin_unsetenv_ext(shell_t *shell, int32_t in_env, int32_t len_arg)
{
    int32_t count = 0;

    for (int32_t i = 0; shell->several_arg_builtin[i] != -1; i++)
        if (shell->several_arg_builtin[i] == -1)
            count++;
    if (count == len_arg - 1)
        in_env = -3;
    if (in_env == -3)
        return;

    if (in_env != -3) {
        int32_t *a = shell->several_arg_builtin;
        if (builtin_unsetenv_loop(shell, a, in_env, len_arg) == 1)
            return;
    }
    return;
}
