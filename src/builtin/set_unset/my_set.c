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

int32_t
is_input_valid_local(shell_t *shell)
{
    if (shell->cmd[2] != NULL) {
        if (shell->cmd[3] != NULL) {
            EXIT_W_ECHO_ERROR_("set: Too many arguments.", 1);
        }
    }
    if (check_set(shell, shell->cmd[1]) == 84)
        return (EXIT_FAILURE);
    return 0;
}

void
init_local_env(shell_t *shell)
{
    shell->local_env = malloc(sizeof(char *) * 2);
    shell->local_env[0] = NULL;
    shell->local_env[1] = NULL;
    (void)shell;
}

int32_t
display_local_env(shell_t *shell)
{
    if (shell->cmd[1] == NULL) {
        for (int i = 0; shell->local_env[i] != NULL; i++) {
            pfflush_wrapper(1, "%s\n", shell->local_env[i]);
        }
        return 1;
    }
    return 0;
}

int32_t
search_existing_var_local(shell_t *shell)
{
    for (int i = 0; shell->local_env[i] != NULL; i++) {
        if (_strncmp(shell->local_env[i], shell->name,
        _strlen(shell->name)) == 0 &&
        shell->local_env[i][_strlen(shell->name)] == '=') {
            shell->local_env[i] = shell->param;
            return 1;
        }
    }
    return 0;
}

int32_t
my_set(shell_t *shell)
{
    COMMAND_FOUND;
    shell->cmd = parse_stdin(shell->get_line, shell);
    if (shell->local_env == NULL) {
        init_local_env(shell);
        return 1;
    }
    if (shell->cmd[1] == NULL)
        return display_local_env(shell);
    if (is_input_valid_local(shell) == EXIT_FAILURE)
        return 84;
    shell->name = shell->cmd[1];
    shell->value = shell->cmd[2];
    shell->param = my_strconcat(shell->name, my_strconcat("=", shell->value));
    if (search_existing_var_local(shell) == 1)
        return 1;
    int32_t len = my_envlen(shell->local_env);
    char *k_v = my_strconcat(shell->cmd[1], my_strconcat("=", shell->cmd[2]));
    shell->local_env = realloc(shell->local_env, sizeof(char *) * (len + 2));
    shell->local_env[len] = k_v;
    shell->local_env[len + 1] = NULL; return 1;
}
