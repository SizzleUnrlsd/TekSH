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
_buf_output(node_t *node, shell_t *shell)
{
    int32_t pipefd[2] = {0};
    char buffer[1096] = {0};
    int32_t wstatus = DEFAULT(wstatus);
    pid_t pid = DEFAULT(pid);
    ssize_t bytesRead = DEFAULT(bytesRead);

    if (pipe(pipefd) == -1) {
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        _p_error(_FORK_ERROR);
        return;
    } else if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        ast(node, shell);
        _exit(EXIT_SUCCESS);
    } else {
        close(pipefd[1]);
        bytesRead = read(pipefd[0], buffer, 1096 - 1);
        if (bytesRead == -1) {
            _p_error(_READ_ERROR);
            exit(_READ_ERROR);
        }
        buffer[bytesRead] = '\0';

        _printf("\n%s", buffer);
        if (bytesRead != 0 && buffer[_strlen(buffer) - 1] != '\n') {
            _print("\n");
        }
        close(pipefd[0]);
        waitpid(pid, &wstatus, WNOHANG);
    }
}

void
ampersand(char *input, node_t *node, shell_t *shell)
{
    pid_t pid;
    int32_t wstatus = DEFAULT(wstatus);

    ++job_control;
    pid = fork();

    if (pid == -1) {
        _p_error(_FORK_ERROR);
        return;
    } else if (pid == 0) {
        _buf_output(node, shell);
        _printf("[%d] %d done\t\t\t\t%s", job_control, getpid(), input);

        if (supposed_job_control > 0) {
            --supposed_job_control;
            kill(getppid(), SIGINT);
        }
        _exit(shell->status);
    } else {
        _printf("[%d] %d\n", job_control, pid);
        waitpid(pid, &wstatus, WNOHANG);
    }
    return;
}