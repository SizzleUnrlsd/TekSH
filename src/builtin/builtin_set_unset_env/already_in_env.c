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

static int32_t 
funct_count(char *str, char c)
{
    int32_t i = 0, e = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            e++;
        i++;
    }
    return (e);
}

static char **
funct_malloc(char *str, char c, char **array)
{
    int32_t i = 0, n = 0, a = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            array[a] = (char*)_mallocbucket(sizeof(char) * (n + 1));
            array[a][n] = '\0';
            a++;
            n = 0;
            i++;
        } else {
            n++;
            i++;
        }
    }
    array[a] = (char*)_mallocbucket(sizeof(char) * (n + 1));
    array[a][n] = '\0';
    return (array);
}

static char **
funct_add_char(char *str, char c, char **array)
{
    int32_t i = 0, n = 0, a = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            n = 0;
            a++;
            i++;
        } else {
            array[a][n] = str[i];
            n++;
            i++;
        }
    }
    array[a][n] = str[i];
    return (array);
}

static char **
static_str_to_word_array_custom(char *str, char c)
{
    int32_t stock = funct_count(str, c);
    char **array = (char**)_mallocbucket(sizeof(char*) * (stock + 2));

    array = funct_malloc(str, c, array);
    array = funct_add_char(str, c, array);
    array[stock + 1] = NULL;
    return array;
}

int32_t
already_in_inv_mode_zero(shell_t *shell, int32_t *a, int32_t count, int32_t e)
{
    char **first_step = NULL;
    char **arg = parse_stdin(shell->line
    );
    char **env = shell->set_env->env_array;
    format_arg(arg);

    if (arg[1][0] == '\0')
        count = -100000;
    for (int32_t i = 0; env[i]; i++) {
        first_step = static_str_to_word_array_custom
        (env[i], '=');
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
    char **arg = parse_stdin(shell->line);

    format_arg(arg);
    first_step = static_str_to_word_array_custom
    (shell->set_env->env_array[i], '=');
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
    char **arg = parse_stdin(shell->line);
    char **env = shell->set_env->env_array; format_arg(arg);

    shell->several_arg_builtin =
    (int*)_mallocbucket(sizeof(int) * len_array(arg));
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
