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

static char *
my_str_dup(char const *src)
{
    int32_t count = DEFAULT(count);
    char *dest = DEFAULT(dest);

    dest = (char*)malloc(sizeof(char) * (_strlen(src) + 1));
    if (!dest) {
        exit(_MEM_ALLOCA_ERROR);
    }

    while (src[count] != '\0') {
        dest[count] = src[count];
        count++;
    }
    dest[count] = '\0';

    return (dest);
}

char *
node_to_string(node_t *node)
{
    if (node == NULL || node->type != NODE_ARGUMENT) {
        return NULL;
    }
    return my_str_dup(node->value);
}
