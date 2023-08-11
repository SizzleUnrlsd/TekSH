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
        case NODE_BACK:
            ampersand(node->left, shell);
            ast(node->right, shell);
            break;
        case NODE_SUBSHELL:
            ast(node->left, shell);
            ast(node->right, shell);
            break;
        case NODE_ARGUMENT:
            {
            /* Exceptional encapsulation due to variable declaration within the switch. */
            char *tmp = DEFAULT(tmp);
            char **arg = DEFAULT(arg);

            shell->line = node->value;
            tmp = update_wildcard(node->value, shell);
            if (tmp == NULL)
                break;
            arg = parse_stdin(tmp);
            execute_command(arg, shell);
            reset_var_shell(shell);
            break;
            }
        default:
            exit(0);
    }
    return;
}

int32_t
ast_final(char *command, shell_t *shell)
{
    int32_t save_0 = DEFAULT(save_0);
    int32_t save_1 = DEFAULT(save_1);
    node_t *root = parse_semicolon(&command, shell);

    save_descriptor(&save_0, &save_1, shell->print);

    if (verbosity == 1) {
        ast_printable(root, shell);
        printf("\n");
    }
    if (noeffect != 1) {
        ast(root, shell);
    }

    descriptor_restoration(save_0, save_1, shell->print);
    return 0;
}
