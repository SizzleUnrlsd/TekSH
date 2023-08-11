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

bool
is_a_sep(char *line)
{
    int cpt = 0;
    char *sep = "><;|";
    while (sep[cpt] != '\0') {
        if (line[0] == sep[cpt]) {
            return true;
        }
        cpt++;
    }
    return false;
}

char *
give_all_options(char **arr_line, int index, shell_t *shell UNUSED_ARG)
{
    int cpt = index;
    int curse = 0, cpy = 0;
    char *cmd_is_replace =
    _mallocbucket(sizeof(char) * (len_needed(arr_line, index)));

    while (arr_line[cpt + 2] != NULL && !is_a_sep(arr_line[cpt + 2])) {
        while (arr_line[cpt + 2][curse] != '\0') {
            cmd_is_replace[cpy] = arr_line[cpt + 2][curse];
            curse++;
            cpy++;
        }
        cmd_is_replace[cpy] = ' ';
        cpy++;
        curse = 0;
        cpt++;
    }
    cmd_is_replace[len_needed(arr_line, index) - 1] = '\0';
    return cmd_is_replace;
}

void
set_alias(call_alias_t *call_alias)
{
    static uint32_t i = 0;
    if (i == 0) {
        call_alias->alias[0] = _mallocbucket(sizeof(alias_t));
        if (!call_alias->alias[0]) {
            _p_error(_MEM_ALLOCA_ERROR);
        }

        call_alias->alias[0]->cmd_alias = strdup("ls");
        call_alias->alias[0]->cmd_is_replace = strdup("ls --color=auto");
        garbage_backup_bucket_ptr((void*)call_alias->alias[0]->cmd_alias);
        garbage_backup_bucket_ptr((void*)call_alias->alias[0]->cmd_is_replace);
        i++;
    }
    return;
}

int
alias_engine(shell_t *shell)
{
    int cpt = 0;
    char **arr_line = _str_to_word_array_custom(shell->line, ' ');
    COMMAND_FOUND;

    while (arr_line[cpt] != NULL) {
        if (strcmp("alias", arr_line[cpt]) == 0 && (arr_line[cpt + 1] == NULL
        || !isalpha(arr_line[cpt + 1][0]))) {
            print_all_alias(shell->call_alias); return true;
        }
        if (len_array(arr_line) == 2 && strcmp("alias", arr_line[cpt]) == 0) {
            return false;
        }
        if (strcmp(arr_line[cpt], "alias") == 0) {
            if_alias_find(shell->call_alias, shell, cpt, arr_line);
            return true;
        }
        cpt++;
    }
    return false;
}
