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
create_node(nodetype type, char *value, ...)
{
    node_t *left = DEFAULT(left);
    node_t *right = DEFAULT(right);
    shell_t *shell = DEFAULT(shell);
    node_t *node = DEFAULT(node);

    va_list ap;
    va_start(ap, value);
    left = va_arg(ap, node_t *);
    right = va_arg(ap, node_t *);
    shell = va_arg(ap, shell_t *);
    node = (node_t *)malloc_attribut(sizeof(node_t), shell);
    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;
    va_end(ap);

    return node;
}
