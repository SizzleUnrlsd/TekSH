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

int32_t is_same_char(char const *path)
{
    char c = '\0';
    char h = ' ';
    char a = '\t';
    char r = '\n';
    int32_t count = DEFAULT(count);
    struct stat st;
    int32_t fd = open(path, O_RDONLY);
    int32_t len_file = stat_copy(path);

    if (len_file == 0)
        return 0;
    if (fd == -1 || fstat(fd, &st) == -1)
        return 1;
    while (read(fd, &c, 1) == 1) {
        if (c == h || c == a || c == r)
            count++;
    }
    if (count == len_file)
        return 0;
    close(fd);

    return -1;
}
