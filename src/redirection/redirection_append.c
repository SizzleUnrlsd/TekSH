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
redirection_append_extend(node_t *node, ...)
{
    shell_t *shell = DEFAULT(shell);
    int32_t fd = DEFAULT(fd);
    char **args = DEFAULT(args);

    va_list ap;
    va_start(ap, node);

    shell = va_arg(ap, shell_t*);
    fd = va_arg(ap, int);
    args = va_arg(ap, char **);

    if (node->type == NODE_REDIRECT_IN) {
        dup2(fd, STDIN_FILENO);
    } else {
        dup2(fd, STDOUT_FILENO);
    }
    close(fd);
    execute_command(args, shell);
    _exit(0);
    va_end(ap);
    return;
}

void
redirection_append_extend_extend(node_t *node, char *file, int32_t *fd)
{
    if (node->type == NODE_REDIRECT_OUT) {
        *fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else if (node->type == NODE_REDIRECT_APPEND) {
        *fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    } else {
        *fd = open(file, O_RDONLY);
    }
    if (*fd < 0) {
        _exit(0);
    }
    return;
}

void
redirection_append(node_t *node, shell_t *shell)
{
    int32_t status = DEFAULT(status);
    int32_t fd = DEFAULT(fd);
    char *args[128] = {0};
    char *cmd = DEFAULT(cmd);
    char *file = DEFAULT(file);

    pid_t pid = fork();
    if (pid < 0) {
        return;
    }
    if (pid == 0) {
        cmd = node_to_string(node->left);
        file = node_to_string(node->right);
        garbage_collector(cmd, shell); garbage_collector(file, shell);
        if (cmd == NULL) {
            ast(node->left, shell);
        }
        file = remove_space_before_string(file);
        if (!file) {
            return;
        }
        del_space_end_str(file);
        parse_command(cmd, args);
        redirection_append_extend_extend(node, file, &fd);
        redirection_append_extend(node, shell, fd, args);
    } else {
        status = 0;
        waitpid(pid, &status, 0);
    }
    return;
}
