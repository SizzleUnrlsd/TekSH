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

char *recup_command(int *nb, shell_t *shell)
{
    char *num = strtok(shell->history->line, "\t");
    if (num == NULL)
        return NULL;
    int n = atoi(num);
    if (n == *nb) {
        char *cut_time = strtok(NULL, "\t");
        if (cut_time == NULL)
            return NULL;
        char *command = strtok(NULL, "\n");
        if (command == NULL)
            return NULL;
        return command;
    }
    return NULL;
}

int execute_command_exclamation(int *read, int *nb, shell_t *shell)
{
    if (*read != -1) {
        char *cmd = recup_command(&*nb, shell);
        _printf("%s\n", cmd);
        system(cmd);
    }
    return 0;
}

int32_t find_in_file(shell_t *shell, int nb)
{
    size_t len = 0;
    int32_t total = 0, read = 0;
    FILE *fd = fopen(PATH_HISTORY_FILE, "r");
    if (fd == NULL)
        return 1;
    shell->history->line = NULL;
    while ((read = getline(&shell->history->line, &len, fd)) != -1) {
        if (shell->history->line[read - 1] == '\n')
            total++;
        if (total == nb) {
            execute_command_exclamation(&read, &nb, shell);
            fclose(fd);
            free(shell->history->line);
            return 0;
        }
    }
    fclose(fd);
    free(shell->history->line);
    pfflush_wrapper(STDERR_FILENO, "%d: Event not found.\n", nb);
    return 1;
}

int32_t
builtin_exclamation(shell_t *shell)
{
    COMMAND_FOUND;
    int32_t future_shell_value = 0;
    char *cmd = strdup(shell->get_line);
    if (cmd[0] == '!') {
        char *exclamation = strchr(cmd, '!');
        int cmd_num = atoi(exclamation + 1);
        if (exclamation != NULL && cmd_num == 0) {
            printf("%s\n", exclamation + 1);
            system(exclamation + 1);
        }
        if (exclamation != NULL && cmd_num >= 0)
            future_shell_value = find_in_file(shell, cmd_num);
        free(cmd);
    }
    if (future_shell_value == 1)
        UPDATE_FAILURE_STATUS;
    if (future_shell_value == 0)
        UPDATE_SUCCESS_STATUS;
    return future_shell_value;
}
