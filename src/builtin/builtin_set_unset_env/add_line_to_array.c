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

char *set_unset_env_ext(int32_t i, char **arg, char **env, char *second_step)
{
    int32_t fmall = _strlen(arg[2]);

    second_step = concat_char_str('=', arg[1], fmall, 1);
    env[i] = second_step;
    env[i] = _strcat(env[i], arg[2]);
    return env[i];
}

void set_unset_in_env(shell_t *shell, char **env, int32_t len_arg)
{
    int32_t i = DEFAULT(i);
    char *second_step = DEFAULT(second_step); char **arg = parse_stdin(shell->get_line, shell);
    char **first_step =
    (char**)malloc_attribut(sizeof(char *) * len_array(env) + 2, shell);
    i = function_set_param_env(i, env, first_step, shell);

    for (int32_t index = 0; env[index]; index++) {
        first_step = _str_to_word_array_custom
        (shell, shell->set_env->env_array[index], '=');
        if ((_strcmp(first_step[0], arg[1]) == 0) && len_arg == 3) {
            free_attribut(env[index], shell);
            garbage_collector
            (set_unset_env_ext(index, arg, env, second_step), shell);
        }
        if ((_strcmp(first_step[0], arg[1]) == 0) && len_arg == 2) {
            arg[2] = " ";
            free_attribut(env[index], shell);
            set_unset_env_ext(index, arg, env, second_step);
        }
    }
    return;
}

void set_in_env_full(shell_t *shell, char **env,
                int32_t len_arg, int32_t in_env)
{
    int32_t i = DEFAULT(i), fmall = DEFAULT(fmall);

    if (len_arg == 3 && in_env == -3) {
        char *second_step = NULL;
        char **arg = parse_stdin(shell->get_line, shell);
        char **first_step =
        (char**)malloc_attribut(sizeof(char *) * (len_array(env) + 2), shell);
        fmall = _strlen(arg[2]);

        i = function_set_param_env(i, env, first_step, shell);

        second_step = concat_char_str('=', arg[1], fmall, 1);
        garbage_collector(second_step, shell);
        first_step[i] = _strcat(second_step, arg[2]);
        first_step[i + 1] = NULL;
        free_attribut(shell->set_env->env_array, shell);
        shell->set_env->env_array = first_step;
    }
    return;
}

void
set_in_env_empty(shell_t* shell, char **env, int32_t len_arg, int32_t in_env)
{
    int32_t i = DEFAULT(i);
    if (len_arg == 2 && in_env == -3) {
        char **arg = parse_stdin(shell->get_line, shell);
        char **first_step =
        (char**)malloc_attribut(sizeof(char *) * (len_array(env) + 3), shell);

        i = function_set_param_env(i, env, first_step, shell);
        first_step[i] = concat_char_str('=', arg[1], 0, 1);
        garbage_collector(first_step[i], shell);
        first_step[i + 1] = NULL;
        shell->set_env->env_array = first_step;
    }
    return;
}

void add_line_to_array(shell_t* shell, int32_t len_arg, int32_t in_env)
{
    char **env = shell->set_env->env_array;

    set_in_env_empty(shell, env, len_arg, in_env);
    set_in_env_full(shell, env, len_arg, in_env);
    if ((len_arg == 3 || len_arg == 2) && in_env != -3)
        set_unset_in_env(shell, env, len_arg);
    return;
}
