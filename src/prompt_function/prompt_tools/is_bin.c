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
is_bin(char const *path)
{
    char c = '\0';
    int32_t count = DEFAULT(count);
    int32_t seuil = 5;
    struct stat st;
    int32_t fd = open(path, O_RDONLY);
    int32_t len_file = stat_copy(path);

    if (fd == -1 || fstat(fd, &st) == -1)
        return !!_FILE_ERROR;
    while (read(fd, &c, 1) == 1) {
        if (!char_isalpha(c) && !char_isdigit(c) && !char_isspace(c))
            count++;
    }
    if (count > (seuil * len_file / 100))
        return 0;
    else
        return 1;
    close(fd);

    return -1;
}
