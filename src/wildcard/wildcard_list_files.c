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

size_t
wildcard_count_dir(char *pwd)
{
    DIR *dir = opendir(pwd);
    if (!dir)
        return 0;
    struct dirent *dirent = readdir(dir);
    size_t count = 0;
    while (dirent != NULL) {
        if (dirent->d_name[0] != '.')
            count++;
        dirent = readdir(dir);
    }
    closedir(dir);
    return count;
}

char **
wildcard_list_files(char *pwd)
{
    size_t count = wildcard_count_dir(pwd);
    char **list = malloc(sizeof(char *) * (count + 1));
    if (!list)
        return NULL;
    list[count] = NULL;
    DIR *dir = opendir(pwd);
    if (!dir)
        return 0;
    struct dirent *dirent = readdir(dir);
    size_t index = 0;
    while (dirent != NULL) {
        if (dirent->d_name[0] != '.')
            list[index++] = strdup(dirent->d_name);
        dirent = readdir(dir);
    }
    closedir(dir);
    return list;
}
