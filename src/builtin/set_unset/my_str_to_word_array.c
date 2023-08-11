/**
 * Copyright (C) 2023 hugo
 * 
 * This file is part of TekSH.
 * 
 * TekSH is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TekSH is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TekSH.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "shell.h"

int separaters(char const *str, char c)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == c)
            return 1;
    return 0;
}

char *change_that(char const *sep, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (separaters(sep, str[i]) == 1)
            str[i] = '\0';
    }
    return str;
}

int count_word(char const *str, char const *sep)
{
    int cnt = 0;
    int in_word = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (separaters(sep, str[i])) {
            in_word = 0;
        } else {
            (!in_word) ? cnt++, in_word = 1 : 0;
        }
    }
    return cnt;
}

char **mstwa(char *str, char const *sep)
{
    int y = DEFAULT(y);
    int nb_word = DEFAULT(nb_word);
    char *cpy = DEFAULT(cpy);
    char **dest = DEFAULT(dest);

    if (str == NULL)
        return NULL;
    cpy = _strdup(str);
    nb_word = count_word(str, sep);
    dest = _malloc(sizeof(char *) * (nb_word + 1));
    if (!dest) {
        return NULL;
    }
    cpy = change_that(sep, cpy);
    for (int i = 0; i < _strlen(str); i++) {
        while (cpy[i] == '\0')
            i++;
        dest[y] = _strdup(cpy + i);
        i += _strlen(dest[y]);
        y++;
    }
    dest[nb_word] = NULL;
    return dest;
}
