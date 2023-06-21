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
display_history(shell_t *shell, char *str)
{
    struct stat buff;
    int fd = open(str, O_RDONLY);
    if (fd == -1)
        return 1;
    stat(str, &buff);
    int size = buff.st_size;
    char *temp = malloc_attribut(sizeof(char) * (size + 1), shell);
    if (read(fd, temp, size) == -1)
        return 1;
    write(1, temp, size);
    temp[size] = '\0';
    close(fd);
    free_attribut(temp, shell);
    return 0;
}

int32_t
builtin_history(shell_t *shell)
{
    COMMAND_FOUND;
    char *str = PATH_HISTORY_FILE;
    if (strncmp(shell->get_line, "history --help", 14) == 0) {
        flag_help();
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (strncmp(shell->get_line, "history -c", 10) == 0) {
        flag_clear(str);
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (strncmp(shell->get_line, "history -S", 10) == 0) {
        char *cmd = strchr(shell->get_line + 11, ' ');
        if (cmd != NULL)
            cmd++;
        UPDATE_SUCCESS_STATUS; return 0;
    }
    display_history(shell, str);
    UPDATE_SUCCESS_STATUS;
    return 0;
}
