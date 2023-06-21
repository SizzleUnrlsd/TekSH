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

flag_handler_t flagHandlers[] = {
    {"--version", handleVersion},
};

void
parse_arg(int32_t ac, char **av)
{

    int32_t nb_flags = sizeof(flagHandlers) / sizeof(flagHandlers[0]);
    if (ac < 2) {
        return;
    }

    for (int32_t i = 0; i < nb_flags; i++) {
        if (strcmp(av[1], flagHandlers[i].flag) == 0) {
            flagHandlers[i].handler();
            return;
        }
    }

    return;
}
