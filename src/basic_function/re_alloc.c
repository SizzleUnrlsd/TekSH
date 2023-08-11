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

char **
re_alloc(shell_t *shell UNUSED_ARG, char **src, int len_src, int len_dest)
{
    int32_t index = 0, e = 0;

    char **nouveau = (char**)
    _mallocbucket(sizeof(char*) * (len_src + len_dest + 2));
    while (index != len_src) {
        nouveau[index] = _strdup(src[index]);
        index++;
    }
    while (e != len_dest) {
        nouveau[index] = "\0";
        index++;
        e++;
    }
    nouveau[index + 1] = NULL;
    return nouveau;
}
