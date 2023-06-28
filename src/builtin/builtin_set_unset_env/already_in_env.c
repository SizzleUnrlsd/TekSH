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

int32_t
already_in_inv_mode_zero(shell_t *shell, int32_t *a, int32_t count, int32_t e)
{
    char **first_step = NULL;
    char **arg = parse_stdin(shell->get_line, shell);
    char **env = shell->set_env->env_array;
    format_arg(arg);

    if (arg[1][0] == '\0')
        count = -100000;
    for (int32_t i = 0; env[i]; i++) {
        first_step = _str_to_word_array_custom
        (shell, env[i], '=');
        if (_strcmp(first_step[0], arg[e]) == 0 && _strlen(arg[e]) > 0) {
            a[e - 1] = i;
            continue;
        } else {
            count++;
        }
    }
    return count;
}

void
already_in_env_mode_one(shell_t *shell, int32_t *a, int32_t i, int32_t count)
{
    int32_t e = 1;
    char **first_step = NULL;
    char **arg = parse_stdin(shell->get_line, shell);
    format_arg(arg);
    first_step = _str_to_word_array_custom
    (shell, shell->set_env->env_array[i], '=');
    if (_strcmp(first_step[0], arg[1]) == 0) {
        a[e - 1] = i;
    } else {
        count++;
    }
    return;
}

int32_t
already_in_env(shell_t *shell, int32_t mode)
{
    int32_t e = 1; int32_t count = 0;
    int32_t *a = NULL;
    char **arg = parse_stdin(shell->get_line, shell);
    char **env = shell->set_env->env_array; format_arg(arg);
    shell->several_arg_builtin =
    (int*)malloc_attribut(sizeof(int) * len_array(arg), shell);
    a = shell->several_arg_builtin;

    for (int32_t i = 0; i != len_array(arg); i++)
        a[i] = -1;
    if (mode == 0) {
        for (; arg[e]; e++)
            count = already_in_inv_mode_zero(shell, a, count, e);
        a[e - 1] = -1; sort_in_int_array(a, len_array(arg) - 1);
        return count;
    }
    if (mode == 1) {
        for (int32_t i = 0; env[i]; i++)
            already_in_env_mode_one(shell, a, i, count);
        a[e] = -1;
    }
    return 0;
}
