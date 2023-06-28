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
parse_redirect_extend(char **input, nodetype *type)
{
    if (**input == '>') {
        *type = NODE_REDIRECT_APPEND;
        (*input)++;
    } else {
        *type = NODE_REDIRECT_OUT;
    }
    return;
}

node_t *
parse_heredoc(char **input, shell_t *shell)
{
    node_t *right = NULL;
    node_t *left = parse_argument(input, shell);
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
    node_t *right = NULL;
    node_t *left = parse_heredoc(input, shell);

    nodetype type;
    if (**input == '>') {
        (*input)++;
        parse_redirect_extend(input, &type);
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
