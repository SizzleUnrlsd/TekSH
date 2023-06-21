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

void check_replace_in_file(int found, FILE *fd, int pos, shell_t *shell)
{
    if (found) {
        fseek(fd, pos, SEEK_SET);
        dprintf(fileno(fd), "%d\t%d:%02d\t%s\n", shell->history->count_n,
        shell->history->hour, shell->history->minute, shell->get_line);
    } else
        dprintf(fileno(fd), "%d\t%d:%02d\t%s\n", shell->history->count_n,
        shell->history->hour, shell->history->minute, shell->get_line);
}

int replace_line_in_file(shell_t *shell, FILE *fd, int *pos, int *found)
{
    char *num = strtok(shell->history->line, "\t");
    if (num == NULL)
        return 1;
    int n = atoi(num);
    if (n == shell->history->count_n - 1) {
        char *cut_time = strtok(NULL, "\t");
        if (cut_time == NULL)
            return 1;
        char *command = strtok(NULL, "\n");
        if (command == NULL)
            return 1;
        if (strcmp(command, shell->get_line) == 0) {
            *pos = ftell(fd) - shell->history->read;
            *found = 1;
            return 2;
        }
    }
    return 0;
}

int write_in_file(shell_t *shell)
{
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    shell->history->hour = local_time->tm_hour;
    shell->history->minute = local_time->tm_min;
    FILE *fd = fopen("42sh_history", "r+");
    if (fd == NULL) return 1;
    shell->history->line = NULL;
    size_t len = 0; int found = 0, pos = 0;
    while ((shell->history->read =
    getline(&shell->history->line, &len, fd)) != -1) {
        if (replace_line_in_file(shell, fd, &pos, &found) == 1)
            continue;
        if (replace_line_in_file(shell, fd, &pos, &found) == 2)
            break;
    }
    check_replace_in_file(found, fd, pos, shell);
    fclose(fd);
    shell->history->count_n++;
    free(shell->history->line);
    return 0;
}
