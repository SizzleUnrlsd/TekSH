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
ast(node_t *node, shell_t *shell)
{
    if (node == NULL) return;
    switch (node->type) {
        case NODE_SEMICOLON:
            ast(node->left, shell);
            ast(node->right, shell);
            break;
        case NODE_PIPE:
            execute_pipeline(node->left, node->right, shell);
            break;
        case NODE_REDIRECT_IN:
        case NODE_REDIRECT_OUT:
        case NODE_REDIRECT_APPEND:
            redirection_append(node, shell);
            break;
        case NODE_REDIRECT_HEREDOC:
            redirection_dup_in(node, shell);
            break;
        case NODE_AND:
            ast(node->left, shell);
            if (shell->status == 1)
                break;
            ast(node->right, shell);
            break;
        case NODE_OR:
            ast(node->left, shell);
            if (shell->status == 0)
                break;
            ast(node->right, shell);
            break;
        case NODE_ARGUMENT:
            shell->get_line = node->value;
            char *tmp = update_wildcard(node->value, shell);
            if (tmp == NULL)
                break;
            char **arg = parse_stdin(tmp, shell);
            execute_command(arg, shell);
            reset_var_shell(shell);
            break;
        default:
            exit_shell(shell);
    }
    return;
}

int32_t
ast_final(char *command, shell_t *shell)
{
    node_t *root = parse_semicolon(&command, shell);
    ast(root, shell);
    return 0;
}
