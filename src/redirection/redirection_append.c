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

static void
_buf_output(node_t *node, shell_t *shell, const char *filename UNUSED_ARG, char *modes UNUSED_ARG)
{
    int32_t pipefd[2] = {0};
    char buffer[8192] = {0};
    int32_t wstatus = DEFAULT(wstatus);
    pid_t pid = DEFAULT(pid);
    ssize_t bytesRead = DEFAULT(bytesRead);
    FILE* file;

    if (pipe(pipefd) == -1) {
        exit(EXIT_FAILURE);
    }

    pid = fork();
    switch (pid) {
        case -1:
        {
            _p_error(_FORK_ERROR);
            return;
            break;
        }
        case 0:
        {
            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);

            ast(node->left, shell);
            fflush(stdout);

            _exit(EXIT_SUCCESS);
            break;
        }
        default:
        {
            close(pipefd[1]);
            file = fopen(filename, modes);
            if (file == NULL) {
                return;
            }
            while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
                fwrite(buffer, sizeof(char), bytesRead, file);
            }

            fclose(file);
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            break;
        }
    }
}

void _buf_input(node_t *node UNUSED_ARG, shell_t *shell UNUSED_ARG, const char *file)
{
    int old_stdin = DEFAULT(old_stdin);
    FILE *input_file = fopen(file, "r");
    if (!input_file) {
        return;
    }

    old_stdin = dup(STDIN_FILENO);

    if (dup2(fileno(input_file), STDIN_FILENO) == -1) {
        fclose(input_file);
        return;
    }

    ast(node->left, shell);
    dup2(old_stdin, STDIN_FILENO);

    fclose(input_file);
}

void
redirection_append(node_t *node, shell_t *shell)
{
    char *file = node_to_string(node->right) + 1;
    
    if (overlap_p(file, node_to_string(node->right), strlen(file), strlen(node_to_string(node->right))))
        _p_error(_OVERLAPPING_ERROR);


    if (file[_strlen(file) - 1] == ' ') {
        file[_strlen(file) - 1] = '\0';
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-enum"
    switch (node->type)
    {
    case NODE_REDIRECT_OUT:
        _buf_output(node, shell, file, "w");
        break;
    case NODE_REDIRECT_APPEND:
        _buf_output(node, shell, file, "a");
        break;
    case NODE_REDIRECT_IN:
        _buf_input(node, shell, file);
        break;
    default:
        break;
    }
#pragma GCC diagnostic pop
    return;
}
