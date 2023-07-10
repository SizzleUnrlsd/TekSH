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

__attribute__((deprecated)) char *
update_wildcard(char *command, shell_t *shell)
{
    char *new_command = DEFAULT(new_command);
    wildcard_t *wildcard = init_wildcard(command);
    if (!wildcard)
        return NULL;

    if (wildcard_convert(wildcard) == 84)
        return NULL;

    new_command = strdup(buffer_get_data(wildcard->new_command));
    if (!new_command)
        return NULL;
    garbage_collector(new_command, shell);
    terminate_wildcard(wildcard);

    return new_command;
}

__attribute__((deprecated)) wildcard_t *
init_wildcard(char *command)
{
    wildcard_t *wildcard = malloc(sizeof(wildcard_t));
    if (!wildcard)
        return NULL;

    wildcard->command = command;
    wildcard->pwd = getcwd(NULL, 0);
    if (!wildcard->pwd)
        return NULL;

    wildcard->file_list = wildcard_list_files(wildcard->pwd);
    if (!wildcard->file_list)
        return NULL;

    wildcard->new_command = init_buffer();
    if (!wildcard->new_command)
        return NULL;

    return wildcard;
}

__attribute__((deprecated)) void
terminate_wildcard(wildcard_t *wildcard)
{
    terminate_buffer(wildcard->new_command);
    free(wildcard->pwd);
    for (int i = 0; wildcard->file_list[i]; i++)
        free(wildcard->file_list[i]);
    free(wildcard->file_list);
    free(wildcard);

    return;
}
