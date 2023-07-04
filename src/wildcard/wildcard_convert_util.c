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

size_t
get_last_space_index(char *command, size_t index)
{
    for (int i = index;i >= 0;i--) {
        if (command[i] == ' ')
            return (size_t)i;
    }
    return 0;
}

size_t
get_next_space_index(char *command, size_t index)
{
    for (size_t i = index;command[i];i++) {
        if (command[i] == ' ')
            return i;
    }
    return strlen(command);
}

char *
wildcard_get_sub_string(char *str, size_t start, size_t end)
{
    size_t index = DEFAULT(index);
    char *sub_str = malloc(sizeof(char) * (end - start + 1));
    if (!sub_str)
        return NULL;

    for (size_t i = start + 1;i < end;i++)
        sub_str[index++] = str[i];
    sub_str[index] = '\0';

    return sub_str;
}

char *
convert_str_to_format(char *str)
{
    char *format = DEFAULT(format);
    size_t index = DEFAULT(index);
    size_t len = strlen(str);

    for (size_t i = 0;str[i];i++) {
        if (str[i] == '*' || str[i] == '?')
            len++;
    }

    format = malloc(sizeof(char) * (len + 1));
    if (!format)
        return NULL;
    format[len] = '\0';

    for (size_t i = 0;str[i];i++) {
        if (str[i] == '*' || str[i] == '?') {
            format[index++] = '.';
            format[index++] = str[i];
        } else
            format[index++] = str[i];
    }

    return format;
}
