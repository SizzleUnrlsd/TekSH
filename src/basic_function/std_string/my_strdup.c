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
_strdup(char const *src,  shell_t *shell)
{
    int32_t count = 0;
    char *dest = NULL;

    dest = (char*)malloc_attribut(sizeof(char) * (_strlen(src) + 1), shell);
    while (src[count] != '\0') {
        dest[count] = src[count];
        count++;
    }
    dest[count] = '\0';
    return (dest);
}
