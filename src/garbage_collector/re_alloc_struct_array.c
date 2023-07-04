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

garbage_collector_t **
realloc_struct(garbage_collector_t **p, size_t size,
                                    unsigned int len)
{
    unsigned int i = 0;
    garbage_collector_t **p_nouveau =
    malloc(sizeof(garbage_collector_t *) * (size));
    for (; p[i]; i++) {
        if (i == LEN_ARRAY_STRUCT)
            break;
        p_nouveau[i] = malloc(sizeof(garbage_collector_t));
        p_nouveau[i]->index = p[i]->index;
        p_nouveau[i]->pointer = p[i]->pointer;
        free(p[i]);
    }
    i++;
    for (; i != len; i++) {
        p_nouveau[i] = malloc(sizeof(garbage_collector_t));
        p_nouveau[i]->index = 0;
        p_nouveau[i]->pointer = NULL;
    }
    free(p);
    return p_nouveau;
}
