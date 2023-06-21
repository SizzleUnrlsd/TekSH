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

int32_t
is_alphanumeric(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c == ' ' || c == '\t' || c == '\n')
        return 1;
    return 0;
}

int32_t
wildcard_convert_loop_get_format(wildcard_t *wildcard, size_t *i,
    wildcard_convert_t *convert)
{
    convert->last_space_index = get_last_space_index(wildcard->command, *i);
    convert->next_space_index = get_next_space_index(wildcard->command, *i);
    if (convert->last_space_index == convert->next_space_index)
        return 84;
    convert->old_last_space_index = convert->last_space_index;
    convert->format = wildcard_get_sub_string(wildcard->command,
        convert->last_space_index, convert->next_space_index);
    if (!convert->format)
        return 84;
    convert->converted_format = convert_str_to_format(convert->format);
    if (!convert->converted_format)
        return 84;
    convert->word_array = wildcard_transform(wildcard,
        convert->converted_format);
    if (!convert->word_array)
        return 84;
    free(convert->converted_format);
    return 0;
}

int32_t
wildcard_convert_loop(wildcard_t *wildcard, size_t *i,
    wildcard_convert_t *convert)
{
    if ((wildcard->command[*i] == '*' || wildcard->command[*i] == '?' ||
        wildcard->command[*i] == '[')
        && (*i == 0 || is_alphanumeric(wildcard->command[*i - 1]))) {
        if (wildcard_convert_loop_get_format(wildcard, i, convert) == 84)
            return 84;
        buffer_back_cursor(wildcard->new_command,
            *i - convert->last_space_index);
        buffer_append(wildcard->new_command, convert->word_array);
        free(convert->word_array);
        *i += strlen(convert->format) - 1;
        free(convert->format);
    } else {
        buffer_append_char(wildcard->new_command,
            wildcard->command[*i]);
    }
    return 0;
}

int32_t
wildcard_convert(wildcard_t *wildcard)
{
    wildcard_convert_t convert = {0, 0, 0, NULL, NULL, NULL};
    for (size_t i = 0;wildcard->command[i];i++) {
        if (wildcard_convert_loop(wildcard, &i, &convert) == 84)
            return 84;
    }
    return 0;
}
