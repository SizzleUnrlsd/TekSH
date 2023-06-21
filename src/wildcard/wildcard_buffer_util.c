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

char *
buffer_get_data(wildcard_buffer_t *buffer)
{
    return buffer->data;
}

size_t
buffer_get_size(wildcard_buffer_t *buffer)
{
    return buffer->size;
}

void
buffer_clear(wildcard_buffer_t *buffer)
{
    memset(buffer->data, 0, buffer->capacity);
    buffer->size = 0;
}

void
buffer_back_cursor(wildcard_buffer_t *buffer, size_t cursor)
{
    buffer->size -= cursor;
    memset(buffer->data + buffer->size, 0, buffer->capacity - buffer->size);
}
