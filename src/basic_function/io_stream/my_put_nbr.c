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
_put_nbr(long nb)
{
    long max = 1;

    if (nb < 0) {
        nb = nb * (-1);
        _putchar('-', 1);
    }
    while (nb / max >= 10) {
        max = max * 10;
    }
    while (max != 0) {
        _putchar((nb / max + 48), 1);
        nb = nb % max;
        max /= 10;
    }
    return nb;
}
