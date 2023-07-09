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
set_error_message(shell_t *shell, char first_char, char special_char, char *context)
{
    uint32_t len_context = _strlen(context);

    if (special_char == '|' || first_char == '|') {
        EXIT_W_ECHO_ERROR_("Invalid null command.", 1);
    }
    if (first_char == '&') {
        EXIT_W_ECHO_ERROR_("Invalid null command.", 1);
    }
    if (context[len_context - 1] == '&' && context[len_context - 2] == '&') {
        EXIT_W_ECHO_ERROR_("Invalid null command.", 1);
    }
    if (special_char == '>' || special_char == '<'
    || first_char == '>' || first_char == '<') {
        EXIT_W_ECHO_ERROR_("Missing name for redirect.", 1);
    }
    return 0;
}

bool
format_getline(shell_t *shell, char **command)
{
    unsigned char first_char = DEFAULT(first_char);
    unsigned char last_char = DEFAULT(last_char);

    remove_backslash_n(*command);
    delete_spaces_tabulations(*command);
    replace_multiple_spaces_tabulations(*command);
    del_space_end_str(*command);
    delete_semicolon_end(*command);
    first_command_is_misplaced(*command, &first_char);
    last_character_not_space_or_tabulation(*command, &last_char);
 
    if (_strcmp(*command, "&&") == 0)
        return true;
    write_in_file(shell);
    if (set_error_message(shell, first_char, last_char, *command)
    || find_shell_inconsistency(*command, shell))
        return true;
    if (*command == NULL || *command[0] == '\0')
        return true;
    return false;
}
