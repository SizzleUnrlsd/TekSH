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
free_attribut(void *p, shell_t *shell)
{
    unsigned int i = DEFAULT(i);

    for (; shell->garbage[i]; i++)
        if (i > 0 && shell->garbage[i - 1]->index < shell->garbage[i]->index)
            continue;
        else
            break;
    for (unsigned int index = 0; index != i; index++)
        if (shell->garbage[index]->pointer == p)
                garbage_uncollector(shell->garbage[index]);
    return;
}
