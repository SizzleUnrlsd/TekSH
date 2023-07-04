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
first_command_is_misplaced(char *command, unsigned char  *c)
{
    (*c) = command[0];

    return;
}

void
last_character_not_space_or_tabulation(char *command, unsigned char  *c)
{
    int32_t len = _strlen(command);

    for (int32_t i = len - 1; i >= 0; i--) {
        if (command[i] != ' ' && command[i] != '\t') {
            (*c) = command[i];
            break;
        }
    }

    return;
}
