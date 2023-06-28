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

static void *
_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;
    char *_d = dest;
    const char *_s = src;

    if (dest == NULL || src == NULL)
        return NULL;

    do {
        _d[i] = _s[i];
        i++;
    } while (i < n);

    return dest;
}

char *
_strndup(const char *s, size_t n)
{
    size_t len = _strnlen(s, n);
    char *new_str = (char *)malloc(len + 1);
    if (!new_str) {
        return NULL;
    }

    _memcpy(new_str, s, len);
    new_str[len] = '\0';

    return new_str;
}
