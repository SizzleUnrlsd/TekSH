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
pfflush(const char *format, va_list ap)
{
    vprintf(format, ap);
    fflush(stdout);
    return;
}

void
vpfflush(const char *format, va_list ap)
{
    vfprintf(stderr, format, ap);
    fflush(stderr);
    return;
}

void pfflush_wrapper(int32_t fd, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    if (fd == 1) {
        va_list ap_copy;
        va_copy(ap_copy, ap);
        pfflush(format, ap_copy);
        va_end(ap_copy);
    } else if (fd == 2) {
        va_list ap_copy;
        va_copy(ap_copy, ap);
        vpfflush(format, ap_copy);
        va_end(ap_copy);
    }
    va_end(ap);
    return;
}
