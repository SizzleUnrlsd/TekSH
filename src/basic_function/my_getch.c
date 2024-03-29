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
_getch(int a)
{
    char buffer[a];
    char *str = NULL;
    int rd = read(STDIN_FILENO, buffer, a);

    buffer[rd - 1] = '\0';
    str = _malloc(sizeof(char) * (rd));
    if (!str) {
        _p_error(_MEM_ALLOCA_ERROR);
    }

    _strcpy(str, buffer);
    return (str);
}
