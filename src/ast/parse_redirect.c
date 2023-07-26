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

node_t *
parse_heredoc(char **input, shell_t *shell)
{
    node_t *right = DEFAULT(right);
    node_t *left = parse_parentheses(input, shell);
    nodetype type;

    if (**input == '<' && *(*input + 1) == '<') {
        (*input)++;
        (*input)++;
        type = NODE_REDIRECT_HEREDOC;
        right = parse_heredoc(input, shell);

        return create_node(type, NULL, left, right, shell);
    }

    return left;
}

node_t *
parse_redirect(char **input, shell_t *shell)
{
    node_t *right = DEFAULT(right);
    node_t *left = parse_heredoc(input, shell);

    nodetype type;
    if (**input == '>') {
        (*input)++;
        if (**input == '>') {
            type = NODE_REDIRECT_APPEND;
            (*input)++;
        } else {
            type = NODE_REDIRECT_OUT;
        }
        right = parse_redirect(input, shell);
        return create_node(type, NULL, left, right, shell);
    } else if (**input == '<' && *(*input + 1) != '<') {
        (*input)++;
        type = NODE_REDIRECT_IN;
        right = parse_redirect(input, shell);
        return create_node(type, NULL, left, right, shell);
    }

    return left;
}
