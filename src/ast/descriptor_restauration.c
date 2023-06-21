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

void
save_descriptor(int32_t *save_0, int32_t *save_1)
{
    (*save_0) = dup(1);
    (*save_1) = dup(0);
    return;
}

void
descriptor_restoration(int32_t save_0, int32_t save_1)
{
    dup2(save_0, 0);
    dup2(save_1, 1);
    return;
}
