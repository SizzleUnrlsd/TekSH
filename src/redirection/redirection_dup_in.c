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
execute_command_with_redirection(shell_t *shell,
                const char *input, node_t *node)
{
    int32_t pipefd[2] = {0};
    pid_t pid;
    if (pipe(pipefd) == -1) {
        _p_error(_PIPE_ERROR);
    }

    pid = fork();
    switch (pid)
    {
    case -1:
        _p_error(_FORK_ERROR);
        _exit(_FORK_ERROR);
        break;
    case 0:
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        ast(node->left, shell);
        _exit(0);
    default:
        close(pipefd[0]);
        if (write(pipefd[1], input, strlen(input)) == -1) {
            _p_error(_WRITE_ERROR);
        }
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
    }
    return;
}

void
redirection_dup_in_extend(shell_t *shell UNUSED_ARG, char *file, char *cmd, ...)
{
    char **arg = DEFAULT(arg);
    char *end_keyword = DEFAULT(end_keyword);
    char *input = DEFAULT(input);

    va_list ap;
    va_start(ap, cmd);

    file = remove_space_before_string(file);
    del_space_end_str(file);

    arg = va_arg(ap, char **);
    parse_command(cmd, arg);
    end_keyword = va_arg(ap, char *);
    strcpy(end_keyword, file);
    strcat(end_keyword, "\n");
    input = va_arg(ap, char *);
    strcpy(input, "");

    va_end(ap);
    return;
}

void
redirection_dup_in(node_t *node, shell_t *shell)
{
    size_t len = DEFAULT(len);
    ssize_t read = DEFAULT(read);
    char *line = DEFAULT(line);
    char *arg[128] = {0};
    char input[4096] = {0};
    char end_keyword[1024] = {0};
    char *cmd = node_to_string(node->left);
    char *file = node_to_string(node->right);

    redirection_dup_in_extend(shell, file, cmd, arg, end_keyword, input);

    while (1) {
        print_str("?", ' ', RD_TTY, 2);
        read = getline(&line, &len, stdin);
        garbage_backup_ptr((void*)line);
        if (read == -1)
            break;
        if (strcmp(line, end_keyword) == 0)
            break;
        strcat(input, line);
    }
    execute_command_with_redirection(shell, input, node);

    return;
}
