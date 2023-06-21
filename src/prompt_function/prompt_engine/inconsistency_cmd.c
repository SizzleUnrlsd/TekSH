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

bool
contains_special_combinations(char* command, char* special_chars)
{
    for (int32_t i = 0; i < _strlen(special_chars); i++) {
        for (int32_t j = 0; j < _strlen(special_chars); j++) {
            char combination[4] =
            {special_chars[i], ' ', special_chars[j], '\0'};
            if (strstr(command, combination)) {
                return true;
            }
        }
    }
    return false;
}

bool
contains_one_multiple(char* command, char* special_chars)
{
    for (int32_t i = 0; i < _strlen(special_chars); i++) {
        for (int32_t j = 1; j < _strlen(special_chars); j++) {
            char combination[4] =
            {special_chars[0], ' ', special_chars[j], '\0'};
            if (strstr(command, combination)) {
                return true;
            }
        }
    }
    return false;
}

int32_t
find_shell_inconsistency(char *command, shell_t *shell)
{
    if (contains_special_combinations(command, "<>")) {
        EXIT_W_ECHO_ERROR_("Missing name for redirect.", 1);
    }
    if (contains_one_multiple(command, "|><|")
    || contains_one_multiple(command, ";|")
    || contains_one_multiple(command, "&><|")) {
        EXIT_W_ECHO_ERROR_("Invalid null command.", 1);
    }
    return 0;
}
