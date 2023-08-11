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
#include "../../../include/set_unset.h"

int is_key_valid_unset(const char *name)
{
    if (name == NULL || name[0] == '\n') {
        my_putstr_error("unsetenv: Too few arguments.\n");
        return 1;
    }
    return 0;
}

int find_key_local(shell_t *shell, char *name)
{
    char **tmp = NULL;
    for (int i = 0; shell->local_env[i] != NULL; i++) {
        tmp = mstwa(shell->local_env[i], "=");
        if (strcmp(tmp[0], name) == 0) {
            return i;
        }
    }
    return -1;
}

char **remove_var_local(shell_t *shell, char *name)
{
    int save = DEFAULT(save);
    int res = DEFAULT(res);
    int j = DEFAULT(j);
    char **tab = DEFAULT(tab);

    if ((res = find_key_local(shell, name)) == -1)
        return shell->local_env;
    else
        save = my_envlen(shell->local_env);
    tab = _malloc(sizeof(char *) * save);
    for (int a = 0; shell->local_env[a] != NULL; a++) {
        if (a != res) {
            tab[j] = strdup(shell->local_env[a]);
            j++;
        }
    }
    tab[j] = NULL;
    return tab;
}

int my_unset(shell_t *shell)
{
    COMMAND_FOUND;
    shell->cmd = mstwa(shell->line, " \t");
    if (shell->local_env == NULL) {
        UPDATE_SUCCESS_STATUS;
    }
    for (int j = 0; shell->cmd[j] != NULL; j++) {
        if (is_key_valid_unset(shell->cmd[j]) != 0)
            return 84;
        shell->local_env = remove_var_local(shell, shell->cmd[j]);
    }
    UPDATE_SUCCESS_STATUS;
    return 0;
}
