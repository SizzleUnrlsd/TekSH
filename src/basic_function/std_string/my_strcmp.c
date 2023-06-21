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

int32_t
cmp_string(char s1, char s2)
{
    if (s1 < s2) {
        return (-1);
    }
    return (1);
}

int32_t
_strcmp(char const *s1, char const *s2)
{
    int32_t n = 0;
    int32_t len_s1 = _strlen(s1);
    int32_t len_s2 = _strlen(s2);

    if (s1[0] == '\0')
        len_s1 = 1;
    else if (s2[0] == '\0')
        len_s2 = 1;

    if (len_s1 != len_s2)
        return (-1);

    while (s1[n] != '\0' && (s2[n]) != '\0') {
        if (s1[n] != s2[n])
            return cmp_string(s1[n], s2[n]);
        n++;
    }
    return (0);
}
