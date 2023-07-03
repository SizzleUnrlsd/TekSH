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

char *my_strconcat(char *src_left, char *src_right)
{
    int i = DEFAULT(i);
    int j = DEFAULT(j);
    char *dest = DEFAULT(dest);

    if (src_right == NULL)
        return src_left;

    dest = malloc(sizeof(char) *
    (_strlen(src_left) + _strlen(src_right) + 1));
    if (dest == NULL)
        return NULL;
    while (src_left[i] != '\0') {
        dest[i] = src_left[i];
        i++;
    }
    while (src_right[j] != '\0') {
        dest[i] = src_right[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}

__attribute__((unused))void
my_putchar_error(char c)
{
    if (write(2, &c, 1) == -1) {
        _p_error(_WRITE_ERROR);
    }
}

__attribute__((deprecated)) void
my_putstr_error(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        my_putchar_error(str[i]);
        i++;
    }
}
