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

__attribute__((deprecated)) int32_t
display_history(shell_t *shell, char *str)
{
    struct stat buff;
    int32_t fd = open(str, O_RDONLY);
    int32_t size = DEFAULT(size);
    char *temp = NULL;

    if (fd == -1) {
        return 1;
    }
    stat(str, &buff);
    size = buff.st_size;
    temp = malloc_attribut(sizeof(char) * (size + 1), shell);
    if (read(fd, temp, size) == -1)
        return 1;
    if (write(1, temp, size) == -1) {
        return !!_WRITE_ERROR;
    }
    temp[size] = '\0';
    close(fd);
    free_attribut(temp, shell);
    return 0;
}

int32_t
builtin_history(shell_t *shell)
{
    char *_default = "history";
    char *cmd = shell->get_line + _strlen(_default) + 1;

    COMMAND_FOUND;
    using_history();

    if (strncmp(cmd, "--help", 14) == 0) {
        flag_help();
        return 0;
    }
    if (strncmp(cmd, "-c", 10) == 0) {
        clear_history();
        return 0;
    }
    if (strncmp(cmd, "-S", 10) == 0) {
        write_history("history.shell");
        return 0;
    }
    if (strcmp(shell->get_line, _default) == 0) {
        HIST_ENTRY** history_entries = history_list();
        if (history_entries != NULL) {
            for (uint64_t i = 0; history_entries[i] != NULL; i++) {
                /* Planned buffering */
                _printf("%d %s\n", (i + 1), history_entries[i]->line);
            }
        }
    }
    UPDATE_SUCCESS_STATUS;
    return 0;
}
