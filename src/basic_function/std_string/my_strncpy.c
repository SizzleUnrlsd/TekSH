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

char *
_strncpy(char *dest, char const *src, uint32_t n)
{
    uint32_t index = 0;
    uint32_t src_len = 0;

    while (src[src_len] != '\0') {
        src_len++;
    }
    if (n > src_len) {
        while (src_len > index) {
            dest[index] = src[index];
            index++;
        }
        dest[index] = '\0';
    } else {
        while (index < n) {
            dest[index] = src[index];
            index++;
        }
    }

    return (dest);
}
