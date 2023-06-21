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

char **
re_alloc(shell_t *shell, char **src, int len_src, int len_dest)
{
    int32_t i = 0, e = 0;
    char **nouveau = (char**)
    malloc_attribut(sizeof(char*) * (len_src + len_dest + 2), shell);
    while (i != len_src) {
        nouveau[i] = _strdup(src[i], shell);
        i++;
    }
    while (e != len_dest) {
        nouveau[i] = "\0";
        i++;
        e++;
    }
    nouveau[i + 1] = NULL;
    for (int i = 0; i != len_src; i++)
        free(src[i]);
    free(src);
    return nouveau;
}
