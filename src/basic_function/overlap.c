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

bool
overlap_p(void * a, void * b, size_t size_a, size_t size_b)
{
    uintptr_t start_a = (uintptr_t)a;
    uintptr_t end_a = start_a + size_a - 1;
    uintptr_t start_b = (uintptr_t)b;
    uintptr_t end_b = start_b + size_b - 1;

    if (start_a == start_b) {
        return true;
    }

    if (start_a < start_b) {
        return end_a >= start_b;
    } else {
        return end_b >= start_a;
    }
}
