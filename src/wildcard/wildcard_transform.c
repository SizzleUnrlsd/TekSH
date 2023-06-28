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

int32_t
wildcard_transform_loop(wildcard_t *wildcard, regex_t *regex,
    wildcard_buffer_t *buffer)
{
    int32_t status = DEFAULT(status);

    for (uint32_t i = 0; wildcard->file_list[i] != NULL; i++) {
        status = regexec(regex, wildcard->file_list[i], 0, NULL, 0);
        if (status == 0) {
            buffer_append(buffer, wildcard->file_list[i]);
            buffer_append_char(buffer, ' ');
            continue;
        }
        if (status == REG_NOMATCH) {
            continue;
        } else {
            return 8;
        }
    }
    return 0;
}

char *
wildcard_transform(wildcard_t *wildcard, char *format)
{
    regex_t regex;
    char *word_array = DEFAULT(word_array);
    wildcard_buffer_t *buffer = init_buffer();
    if (!buffer)
        return NULL;

    buffer_append_char(buffer, ' ');
    if (regcomp(&regex, format, REG_EXTENDED) != 0)
        return NULL;
    if (wildcard_transform_loop(wildcard, &regex, buffer) != 0)
        return NULL;
    regfree(&regex);
    word_array = strdup(buffer_get_data(buffer));
    terminate_buffer(buffer);
    return word_array;
}
