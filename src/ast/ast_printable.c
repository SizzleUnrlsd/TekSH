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
ast_printable(node_t *node, shell_t *shell)
{
    if (node == NULL) return;
    switch (node->type) {
        case NODE_SEMICOLON:
            ast_printable(node->left, shell);
            _print(" ; ");
            ast_printable(node->right, shell);
            break;
        case NODE_PIPE:
            ast_printable(node->left, shell);
            _print(" | ")
            ast_printable(node->right, shell);
            break;
        case NODE_REDIRECT_IN:
        case NODE_REDIRECT_OUT:
        case NODE_REDIRECT_APPEND:
            ast_printable(node->left, shell);
            if (node->type == NODE_REDIRECT_IN)
                _print(" < ");
            if (node->type == NODE_REDIRECT_OUT)
                _print(" > ");
            if (node->type == NODE_REDIRECT_APPEND)
                _print(" >> ");
            ast_printable(node->right, shell);
            break;
        case NODE_REDIRECT_HEREDOC:
            ast_printable(node->left, shell);
            _print(" << ");
            ast_printable(node->right, shell);
            break;
        case NODE_AND:
            ast_printable(node->left, shell);
            _print(" && ");
            ast_printable(node->right, shell);
            break;
        case NODE_OR:
            ast_printable(node->left, shell);
            _print(" || ");
            ast_printable(node->right, shell);
            break;
        case NODE_BACK:
            ast_printable(node->left, shell);
            _print(" & ");
            ast_printable(node->right, shell);
            break;
        case NODE_SUBSHELL:
            break;
        case NODE_ARGUMENT:
            {
            _printf("%s", node->value);
            break;
            }
        default:
            exit_shell(shell);
    }
    return;
}
