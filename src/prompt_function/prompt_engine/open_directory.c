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

static char *
arg_formater(char **arg, char *without_n)
{
    for (int32_t i = 0; arg[i] != NULL; i++)
        if (arg[i][0] == '\0')
            arg[i] = NULL;
    if (arg[0][_strlen(arg[0]) - 1] == '\n') {
        remove_back_n(arg[0]);
    } else
        without_n = arg[0];

    return without_n;
}

int32_t
command_is_here(char *command, char *dir, int32_t len_arg, shell_t *shell)
{
    char command_path[256] = {0};

    if (command == NULL)
        return 1;
    if (dir[0] == '.' && len_arg == 1) {
        pfflush_wrapper(STDERR_FILENO, "/usr/bin/.");
        EXIT_W_ECHO_ERROR_(": Permission denied.", 1);
        return 1;
    }
    snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);
    if (access(command_path, X_OK) == -1) {
        print_str(command_path, 0, true, 2);
        EXIT_W_ECHO_ERROR_(": Command not found.", 1);
        return 1;
    } else {
        return 0;
    }
    return 0;
}

void
go_to_dollar_engine(char **arg, int32_t shell_status, shell_t *shell)
{
    for (int32_t i = 0; arg[i]; i++) {
        if (arg[i][0] == '$') {
            shell_status = dollar_engine(arg, i, shell);
            if (shell_status == 1) {
                exit(1);
            }
        }
    }
}

int32_t
open_directory(shell_t *shell, char **path, char **arg)
{
    char *concat_first_step = DEFAULT(concat_first_step), *concat_second_step = DEFAULT(concat_second_step);
    char *without_n = DEFAULT(without_n);
    int32_t fmall = DEFAULT(fmall), shell_status = DEFAULT(shell_status);

    if (arg[0][0] == '.' && command_is_here(arg[0] + 2, chr_to_str(arg[0][0]), _strlen(arg[0]), shell) == 1) {
        exit(1);
    }
    without_n = arg_formater(arg, without_n);
    go_to_dollar_engine(arg, shell_status, shell);
    if (path == NULL) {
        access_file(shell, arg);
        return 1;
    }
    for (int32_t i = 0; path[i]; i++) {
        fmall = _strlen(without_n);
        concat_first_step = concat_char_str('/', path[i], fmall, 1);
        concat_second_step = (char *)_malloc(sizeof(char)
        * (_strlen(concat_first_step) + 1));
        concat_second_step = _strcat(concat_first_step, without_n);
        execve(concat_second_step, arg, shell->set_env->env_array);
    }
    return 0;
}
