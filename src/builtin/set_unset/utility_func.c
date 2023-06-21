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
#include "../../../include/set_unset.h"

char **duparray(char **array)
{
    int i = 0;
    while (array[i] != NULL)
        i++;
    char **dup = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (array[i] != NULL) {
        dup[i] = strdup(array[i]);
        i++;
    }
    dup[i] = NULL;
    return dup;
}

int my_envlen(char **array)
{
    int i = 0;
    while (array[i] != NULL)
        i++;
    return i;
}
