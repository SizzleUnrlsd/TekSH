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

bool verbosity = false;

bool noeffect = false;

static inline void
verbose_opt(void)
{
    verbosity = true;
}

static inline void
noeffect_opt(void)
{
    noeffect = true;
}

flag_handler_t flaghandlers[] = {
    {"--version", handleVersion},
    {"--verbose", verbose_opt},
    {"--noeffect", noeffect_opt},
};

void
parse_arg(int32_t ac, char **av)
{

    int32_t nb_flags = sizeof(flaghandlers) / sizeof(flaghandlers[0]);
    if (ac < 2) {
        return;
    }

    for (int32_t i = 1; i != ac; ++i) {
        for (int32_t e = 0; e != nb_flags; ++e) {
            if (strcmp(av[i], flaghandlers[e].flag) == 0) {
                flaghandlers[e].handler();
            }
        }
    }

    return;
}
