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

char *
replace_line(char *cmd, char *actual, char *replace)
{
    char *result = NULL, *insert = NULL, *tmp = NULL;
    int32_t len_act = 0;
    int32_t len_replace = 0;
    int32_t len_ft_mall = 0;
    int32_t count = 0;

    if (!cmd || !actual)
        return NULL;

    (!replace ? replace = "" : 0);
    len_act = strlen(actual), len_replace = strlen(replace),
    len_ft_mall = 0, count = 0;
    if (len_act == 0)
        return NULL;

    insert = cmd;
    for (count = 0; (tmp = strstr(insert, actual)); count++)
        insert = tmp + len_act;
    tmp = result = _malloc(strlen(cmd) +(len_replace - len_act) * count + 1);
    if (!result)
        return NULL;

    while (count--) {
        insert = strstr(cmd, actual); len_ft_mall = insert - cmd;
        tmp = strncpy(tmp, cmd, len_ft_mall) + len_ft_mall;
        tmp = strcpy(tmp, replace) + len_replace; cmd += len_ft_mall + len_act;
    }
    strcpy(tmp, cmd);
    return result;
}

char *
parse_aliases(call_alias_t *call_alias, char *cmd, char *cmp, char *new)
{
    int32_t curse = 0;

    while (call_alias->alias[curse] != NULL) {
        if (strcmp(cmp, call_alias->alias[curse]->cmd_alias) == 0) {
            new = replace_line(cmd, cmp,
            call_alias->alias[curse]->cmd_is_replace);
            call_alias->info_alias->is_an_alias = true;
            break;
        }
        curse++;
    }
    if (new == NULL)
        call_alias->info_alias->is_an_alias = false;

    return new;
}

char *
format_alias_getline(shell_t *shell, char *cmd)
{
    uint32_t cpt = 0;
    char *new_line = NULL;
    char **arr_line = _str_to_word_array_custom(cmd, ' ');

    set_alias(shell->call_alias);

    while (arr_line[cpt] != NULL) {
        if (strcmp("alias", arr_line[cpt]) == 0) {
            new_line = NULL;
            shell->call_alias->info_alias->is_an_alias = false;
            break;
        }
        new_line = parse_aliases(shell->call_alias, cmd,
        arr_line[cpt], new_line);
        cpt++;
    }

    return new_line;
}
