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

int32_t funct_count(char *str, char c)
{
    int32_t i = 0, e = 0;

    while (str[i] != '\0') {
        if (str[i] == c)
            e++;
        i++;
    }
    return (e);
}

char **funct_malloc(shell_t *shell, char *str, char c, char **array)
{
    int32_t i = 0, n = 0, a = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            array[a] = (char*)malloc_attribut(sizeof(char) * (n + 1), shell);
            array[a][n] = '\0';
            a++;
            n = 0;
            i++;
        } else {
            n++;
            i++;
        }
    }
    array[a] = (char*)malloc_attribut(sizeof(char) * (n + 1), shell);
    array[a][n] = '\0';
    return (array);
}

char **funct_add_char(char *str, char c, char **array)
{
    int32_t i = 0, n = 0, a = 0;

    while (str[i] != '\0') {
        if (str[i] == c) {
            n = 0;
            a++;
            i++;
        } else {
            array[a][n] = str[i];
            n++;
            i++;
        }
    }
    array[a][n] = str[i];
    return (array);
}

char **
_str_to_word_array_custom(shell_t *shell, char *str, char c)
{
    int32_t stock = funct_count(str, c);
    char **array = (char**)malloc_attribut(sizeof(char*) * (stock + 2), shell);
    array = funct_malloc(shell, str, c, array);
    array = funct_add_char(str, c, array);
    array[stock + 1] = NULL;
    return (array);
}
