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
del_one_char(shell_t *shell, char **src, char *dest)
{
    dest = (char*)malloc_attribut(sizeof(char) * (_strlen(src[0])), shell);
    dest = _strncpy(dest, src[0], 2);

    return dest;
}

char *
remove_back_n(char *src)
{
    int32_t len = _strlen(src);

    if (src[len - 1] != '\n')
        return src;

    if (len > 0)
        src[len - 1] = '\0';

    return src;
}
