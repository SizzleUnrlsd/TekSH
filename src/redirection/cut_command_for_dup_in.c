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

static void
format_command(char **command)
{
    int32_t len_command = strlen(*command);

    if ((*command) == NULL) {
        return;
    }
    if (command[0][0] == ' ') {
        (*command)++;
        len_command--;
    }
    if (command[0][len_command - 1] == ' ') {
        command[0][len_command - 1] = '\0';
    }

    return;
}

char *
cut_into_command(char *command)
{
    char *end = DEFAULT(end);
    char *str = DEFAULT(str);
    char *ptr_command = DEFAULT(ptr_command);
    char *start = strstr(command, "<<");
    if (start == NULL) {
        return NULL;
    }
    start += 2;
    end = strchr(start, '>');
    if (end == NULL) {
        return NULL;
    }
    str = (char*)malloc(sizeof(char) *(end - start + 1));
    strncpy(str, start, end - start);
    str[end - start] = '\0';
    ptr_command = strdup(str);
    format_command(&ptr_command);

    return ptr_command;
}
