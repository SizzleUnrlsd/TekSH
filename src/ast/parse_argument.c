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
parse_argument(char **input, shell_t *shell)
{
    char *value = DEFAULT(value);
    char *start = *input;

    while (**input != '\0' && **input != '|'
        && **input != ';' && **input != '>'
        && **input != '<' && **input != '&'
        && **input != ')') {
            (*input)++;
    }
    value = _strndup(start, *input - start);
    return create_node(NODE_ARGUMENT, value, NULL, NULL, shell);
}
