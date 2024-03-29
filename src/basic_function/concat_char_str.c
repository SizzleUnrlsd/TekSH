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

char *
concat_char_str(char concat, char *str, int32_t futur, int32_t a)
{
    int32_t len_str = _strlen(str);
    char *dest = (char*)_mallocbucket(sizeof(char) * (len_str + futur + 2));

    if (a == 0) {
        dest[0] = concat;
        for (int32_t i = 1; i != len_str + 1; i++) {
            dest[i] = str[i - 1];
        }
    }

    if (a == 1) {
        for (int32_t i = 0; i != len_str + 1; i++) {
            dest[i] = str[i];
        }
        dest[len_str] = concat;
    }
    dest[len_str + 1] = '\0';

    return dest;
}
