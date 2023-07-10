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

static
uint32_t index_integer(void)
{
    static uint32_t index = DEFAULT(index);
    index++;

    return index;
}

void init_struct(garbage_collector_t *garbage)
{
    garbage->index = DEFAULT(garbage->index);
    garbage->pointer = DEFAULT(garbage->pointer);
    return;
}

void garbage_collector_extend(void *p, int index_, shell_t *shell)
{
    garbage_collector_t *garbage = malloc(sizeof(garbage_collector_t));
    if (!garbage) {
        _p_error(_MEM_ALLOCA_ERROR);
    }

    init_struct(garbage);
    garbage->index = index_ - 1;
    shell->io++;
    if (p == NULL)
        return;
    garbage->pointer = p;
    shell->garbage[index_ - 1] = garbage;

    return;
}

void garbage_collector(void *p, shell_t *shell)
{
    static size_t acceptance_limit = LEN_ARRAY_STRUCT - 500;
    unsigned int index_ = index_integer();

    if (index_ >= acceptance_limit) {
        acceptance_limit = acceptance_limit + 5000;
        shell->garbage =
        realloc_struct(shell->garbage, acceptance_limit, index_);
    }
    garbage_collector_extend(p, index_, shell);

    return;
}
