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

void
pre_set_alias(call_alias_t *call_alias, shell_t *shell,
                            char **arr_line, int index)
{
    call_alias->alias[call_alias->info_alias->nb] = NULL;
    call_alias->alias[call_alias->info_alias->nb] =
    malloc_attribut(sizeof(alias_t), shell);
    call_alias->alias[call_alias->info_alias->nb]->cmd_alias =
    strdup(arr_line[index + 1]);
    call_alias->alias[call_alias->info_alias->nb]
    ->cmd_alias[strlen(arr_line[1])] = '\0';
    call_alias->alias[call_alias->info_alias->nb]->cmd_is_replace =
    give_all_options(arr_line, index, shell);
}

void
resize_alias_array(call_alias_t *call_alias, shell_t *shell)
{
    static size_t acceptance_limit = SET_ALIAS - ACCEPTANCE;
    if (call_alias->info_alias->nb >= SET_ALIAS - ACCEPTANCE) {
        call_alias->info_alias->current_alloc = call_alias->info_alias->nb;
        call_alias->alias =
        realloc(call_alias->alias, sizeof(alias_t) * SET_ALIAS);
        garbage_collector(call_alias->alias, shell);
        acceptance_limit = acceptance_limit + SET_ALIAS;
    }
    if (call_alias->info_alias->nb >= acceptance_limit - ACCEPTANCE) {
        call_alias->alias =
        realloc(call_alias->alias, sizeof(alias_t) * SET_ALIAS);
        garbage_collector(call_alias->alias, shell);
        acceptance_limit = acceptance_limit + SET_ALIAS;
    }
}

int
verif_exists(int cpt, char *line_cmp, char **arr_line, shell_t *shell)
{
    int curse = 0;
    if (cpt > 1 && strcmp(arr_line[cpt - 1], "alias") != 0)
        return 0;
    while (shell->call_alias->alias[curse] != NULL) {
        if (strcmp(shell->call_alias->alias[curse]->cmd_alias,
        line_cmp) == 0) {
            shell->call_alias->alias[curse]->cmd_is_replace =
            give_all_options(arr_line, cpt - 1, shell);
            return 1;
        }
        curse++;
    }
    return 0;
}

int
alias_already_exist(shell_t *shell, char **arr_line)
{
    int cpt = 0;
    if (len_array(arr_line) == 2)
        return 0;
    while (arr_line[cpt] != NULL) {
        if (verif_exists(cpt, arr_line[cpt], arr_line, shell) == 1)
            return 1;
        cpt++;
    }
    return 0;
}

void
if_alias_find(call_alias_t *call_alias, shell_t *shell, int cpt,
                                                char **arr_line)
{
    resize_alias_array(call_alias, shell);
    if (alias_already_exist(shell, arr_line) == 0) {
        pre_set_alias(call_alias, shell, arr_line, cpt);
        remove_backslash_n(call_alias->alias[call_alias->info_alias->nb]
        ->cmd_is_replace);
        call_alias->info_alias->nb++;
    }
    free_attribut(arr_line, shell);
}
