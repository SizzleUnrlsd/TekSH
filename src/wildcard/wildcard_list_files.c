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

size_t
wildcard_count_dir(char *pwd)
{
    size_t count = DEFAULT(count);
    struct dirent *dirent = DEFAULT(dirent);
    DIR *dir = opendir(pwd);
    if (!dir)
        return 0;

    dirent = readdir(dir);
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
    size_t index = DEFAULT(index);
    struct dirent *dirent = DEFAULT(dirent);
    DIR *dir = DEFAULT(dir);
    char **list = malloc(sizeof(char *) * (count + 1));
    if (!list)
        return NULL;
    list[count] = NULL;

    dir = opendir(pwd);
    if (!dir)
        return 0;

    dirent = readdir(dir);
    while (dirent != NULL) {
        if (dirent->d_name[0] != '.')
            list[index++] = strdup(dirent->d_name);
        dirent = readdir(dir);
    }
    closedir(dir);

    return list;
}
