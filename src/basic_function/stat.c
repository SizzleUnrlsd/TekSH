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
stat_copy(char const *str)
{
    char buffer[1];
    int32_t n = 0;
    int32_t size = 0;
    int32_t open_fd = open(str, O_RDONLY);

    if (open_fd == -1) {
        return -1;
    }
    while ((n = read(open_fd, buffer, 1)) > 0)
        size += n;
    close(open_fd);
    return (size);
}
