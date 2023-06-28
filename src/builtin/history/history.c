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
display_history(shell_t *shell, char *str)
{
    struct stat buff;
    int32_t fd = open(str, O_RDONLY);
    int32_t size = 0;
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
    char *str = PATH_HISTORY_FILE;
    char *cmd = DEFAULT(cmd);
    COMMAND_FOUND;

    if (strncmp(shell->get_line, "history --help", 14) == 0) {
        flag_help();
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (strncmp(shell->get_line, "history -c", 10) == 0) {
        flag_clear(str);
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (strncmp(shell->get_line, "history -S", 10) == 0) {
        cmd = strchr(shell->get_line + 11, ' ');
        if (cmd != NULL)
            cmd++;
        UPDATE_SUCCESS_STATUS; return 0;
    }
    display_history(shell, str);
    UPDATE_SUCCESS_STATUS;
    return 0;
}
