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
__attribute__((unused)) int32_t
find_wrong_exe(char *path)
{
    for (; *path; path++)
        if (_strncmp(path, "exe", 3) == 0)
            return 0;
    return -1;
}

__attribute__((deprecated)) int32_t
access_file_extend(shell_t *shell, char **path)
{
    if (is_dir(path[0]) == 0) {
        _putstr(path[0], 2);
        EXIT_W_ECHO_ERROR_(": Permission denied.", 1)
    }
    if (access(path[0], F_OK) == 0 && access(path[0], X_OK) == 0
            && is_bin(path[0]) == 0 && find_wrong_exe(path[0]) == 0) {
        _putstr(path[0], 2);
        _putstr(": ", 2);
        _putstr(path[0], 2);
        EXIT_W_ECHO_ERROR_(": Exec format error. Wrong Architecture.", 1);
    }
    return 0;
}

int32_t
execution_test(shell_t *shell, char **path)
{
    execve(path[0], path, shell->set_env->env_array);
    if (errno == ENOEXEC) {
        _putstr(path[0], 2);
        EXIT_W_ECHO_ERROR_(": Exec format error. Wrong Architecture.", 1);
    }
    if (errno == EACCES) {
        _putstr(path[0], 2);
        EXIT_W_ECHO_ERROR_(": Permission denied.", 1);
    }
    return 0;
}

int32_t
access_file(shell_t *shell, char **path)
{
    format_arg(path);
    for (int32_t i = 0; path[i]; i++) {
        if (path[i][0] == '$') {
            dollar_engine(path, 0, shell);
            return 1;
        }
    }
    if (access(path[0], F_OK) == -1) {
        print_str(path[0], 0, true, 2);
        EXIT_W_ECHO_ERROR_(": Command not found.", 1);
    } else if (access(path[0], X_OK) == -1) {
        _putstr(path[0], 2);
        EXIT_W_ECHO_ERROR_(": Permission denied.", 1);
    } else {
        execution_test(shell, path);
    }
    return 0;
}
