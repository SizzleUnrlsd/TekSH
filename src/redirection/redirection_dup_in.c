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

void
execute_command_with_redirection(shell_t *shell,
                const char *input, node_t *node)
{
    int32_t pipefd[2] = {0};
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        ast(node->left, shell);
        exit(0);
    } else {
        close(pipefd[0]);
        write(pipefd[1], input, strlen(input));
        close(pipefd[1]);
        waitpid(pid, NULL, 0);
    }
    return;
}

void
redirection_dup_in_extend(shell_t *shell, char *file, char *cmd, ...)
{
    file = remove_space_before_string(file);
    garbage_collector(file, shell);
    del_space_end_str(file);

    va_list ap;
    va_start(ap, cmd);

    char **arg = va_arg(ap, char **);
    parse_command(cmd, arg);
    char *end_keyword = va_arg(ap, char *);
    strcpy(end_keyword, file);
    strcat(end_keyword, "\n");
    char *input = va_arg(ap, char *);
    strcpy(input, "");
    va_end(ap);
    return;
    (void) shell;
}

void
redirection_dup_in(node_t *node, shell_t *shell)
{
    size_t len = 0;
    ssize_t read = 0;
    char *line = NULL;
    char *arg[128] = {0};
    char input[4096] = {0};
    char end_keyword[1024] = {0};
    char *cmd = node_to_string(node->left);
    char *file = node_to_string(node->right);
    redirection_dup_in_extend(shell, file, cmd, arg, end_keyword, input);
    while (1) {
        print_str("?", ' ', RD_TTY, 1);
        read = getline(&line, &len, stdin);
        if (read == -1)
            break;
        if (strcmp(line, end_keyword) == 0)
            break;
        strcat(input, line);
    }
    execute_command_with_redirection(shell, input, node);
    return;
}
