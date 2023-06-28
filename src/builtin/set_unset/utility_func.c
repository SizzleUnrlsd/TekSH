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
    int index = DEFAULT(index);
    char **dup = DEFAULT(dup);

    while (array[index] != NULL)
        index++;

    dup = malloc(sizeof(char *) * (index + 1));
    if (!dup) {
        _p_error(_MEM_ALLOCA_ERROR);
    }
    index = 0;
    while (array[index] != NULL) {
        dup[index] = strdup(array[index]);
        index++;
    }
    dup[index] = NULL;
    return dup;
}

int my_envlen(char **array)
{
    int32_t index = DEFAULT(index);

    while (array[index] != NULL)
        index++;
    return index;
}
