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
sign(char const *str)
{
    int b = 1;
    int a = 0;

    while (str[a] == '-' || str[a] == '+') {
        if (str[a] == '-') {
            b = b * (- 1);
        } else {
            b = b * 1;
        }
    a++;
    }
    return (b);
}

int32_t
_get_nbr(char const *str)
{
    int32_t index = 0;
    int32_t result = 0;

    while ((str[index] >= '0' && str[index] <= '9')
    || (str[index] == '-' || str[index] == '+')) {
        if (str[index] >= 48 && str[index] <= 57) {
            result = result + (str[index] - 48);
            result = result * 10;
        }
        index++;
    }
    result = result * sign(str);
    result = result / 10;
    return (result);
}
