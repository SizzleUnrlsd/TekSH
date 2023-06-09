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
_str_dup(char const *src)
{
    int32_t a = DEFAULT(a);
    char *dest = NULL;

    dest = (char*)malloc(sizeof(char) * (_strlen(src) + 1));
    while (src[a] != '\0') {
        dest[a] = src[a];
        a++;
    }
    dest[a] = '\0';

    return (dest);
}

char *
remove_space_before_string(const char *command)
{
    if (command == NULL) {
        return NULL;
    }
    while (*command != '\0' && *command == ' ') {
        command++;
    }

    return _str_dup(command);
}
