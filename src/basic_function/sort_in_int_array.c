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

void sort_in_int_array_extend(int *a, int i, int j, int temp)
{
    if (a[i] > a[j]) {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    return;
}

void sort_in_int_array(int *a, int len)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for (i = 0; i < len - 1; i++) {
        for (j = i + 1; j < len; j++) {
            sort_in_int_array_extend(a, i, j, temp);
        }
    }
    return;
}
