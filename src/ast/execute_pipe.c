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
terminate_pipe(shell_t *shell, int32_t *pipefd, ...)
{
    va_list args;
    int32_t rt_1 = DEFAULT(rt_1);
    int32_t rt_2 = DEFAULT(rt_2);

    close(pipefd[0]);
    close(pipefd[1]);
    va_start(args, pipefd);

    rt_1 = va_arg(args, int32_t);
    rt_2 = va_arg(args, int32_t);

    if (rt_1 == 0 && rt_2 == 0) {
        shell->status = 0;
    }
    if (rt_1 != 0 || rt_2 != 0) {
        shell->status = 1;
    }
    va_end(args);
}

uint32_t
pipe_child_process(shell_t *shell, pid_t pid1, int32_t *pipefd,
                                                node_t *cmd1_node)
{
    uint32_t return_value_shell_1 = DEFAULT(return_value_shell_1);

    if (pid1 == 0) {
        shell->status = RESET(shell->status);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        ast(cmd1_node, shell);
        return_value_shell_1 = shell->status;
        _exit(return_value_shell_1);
    }
    return return_value_shell_1;
}

__attribute__((deprecated)) int32_t
pipe_child_normal_process(shell_t *shell, pid_t pid1, int32_t *pipefd, ...)
{
    pid_t pid2;
    node_t *cmd2_node = DEFAULT(cmd2_node);
    int32_t return_value_shell_1 = DEFAULT(return_value_shell_1);
    int32_t return_value_shell_2 = DEFAULT(return_value_shell_2);

    va_list ap;
    va_start(ap, pipefd);
    cmd2_node = va_arg(ap, node_t*);
    return_value_shell_1 = va_arg(ap, uint32_t);
    va_end(ap);

    pid2 = fork();
    if (pid2 == 0 && cmd2_node != NULL) {
        shell->status = DEFAULT(shell->status);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); close(pipefd[1]);
        ast(cmd2_node, shell);
        return_value_shell_2 = shell->status;
        waitpid(pid1, NULL, 0);
        _exit(0);
        EXIT_W_ECHO_ERROR_("Command not found.", EXIT_FAILURE);
    }
    terminate_pipe(shell, pipefd, pid1, pid2,
    return_value_shell_1, return_value_shell_2);
    return 0;
}

__attribute__((deprecated)) int32_t
pipe_child_with_no_printable_process(shell_t *shell, pid_t pid1,
                                            int32_t *pipefd, ...)
{
    node_t *cmd2_node = DEFAULT(cmd2_node);
    int32_t return_value_shell_1 = DEFAULT(return_value_shell_1);
    int32_t return_value_shell_2 = DEFAULT(return_value_shell_2);

    va_list ap;
    va_start(ap, pipefd);
    cmd2_node = va_arg(ap, node_t*);
    return_value_shell_1 = va_arg(ap, uint32_t);
    va_end(ap);

    if (cmd2_node->value != NULL
    && is_builtin(shell, cmd2_node->value) != -1) {
        shell->status = 0;
        close(pipefd[0]); close(pipefd[1]);
        ast(cmd2_node, shell);
        return_value_shell_2 = shell->status;
        waitpid(pid1, NULL, 0);
        terminate_pipe(shell, pipefd, pid1, 0,
        return_value_shell_1, return_value_shell_2);
        return 0;
    }
    return 0;
}

int32_t
execute_pipeline(node_t *cmd1_node, node_t *cmd2_node, shell_t *shell)
{
    int32_t pipefd[2] = {0};
    pid_t pid1;
    int32_t  return_value_shell_1 = DEFAULT(return_value_shell_1);
    int32_t return_value_shell_2 = DEFAULT(return_value_shell_2);

    if (pipe(pipefd) == -1)
        return 1;

    pid1 = fork();
    if (pid1 == -1) {
        return !!_FORK_ERROR;
    }

    pipe_child_process(shell, pid1, pipefd, cmd1_node);
    if (pid1 != 0) {
        shell->status = RESET(shell->status);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        ast(cmd2_node, shell);
        waitpid(pid1, &return_value_shell_1, 0);
        return_value_shell_2 = shell->status;
        terminate_pipe(shell, pipefd, return_value_shell_1,
        return_value_shell_2);
    }
    return 0;
}
