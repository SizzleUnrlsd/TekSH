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

void
delete_spaces_tabulations(char *command)
{
    int32_t i = DEFAULT(i), j = DEFAULT(j);
    int32_t len = _strlen(command);

    if (check_shell_line(command))
        return;

    for (i = 0; i < len && (command[i] == ' ' || command[i] == '\t'); i++);

    if (i > 0) {
        for (j = 0; j < len - i; j++) {
            command[j] = command[j + i];
        }
        command[j] = '\0';
    }
    return;
}
