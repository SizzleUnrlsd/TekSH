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

wildcard_buffer_t *
init_buffer(void)
{
    wildcard_buffer_t *buffer = _malloc(sizeof(wildcard_buffer_t));
    if (!buffer)
        return (NULL);
    buffer->data = _malloc(sizeof(char) * (BUFFER_BLOCK_SIZE + 1));
    if (!buffer->data)
        return (NULL);
    memset(buffer->data, 0, sizeof(char) * (BUFFER_BLOCK_SIZE + 1));
    buffer->capacity = BUFFER_BLOCK_SIZE;
    buffer->size = 0;
    return buffer;
}

int32_t
buffer_append(wildcard_buffer_t *buffer, char *data)
{
    size_t data_len = DEFAULT(data_len);

    if (!buffer || !data)
        return EXIT_FAILURE;

    data_len = strlen(data);
    while (buffer->size + data_len >= buffer->capacity) {
        buffer->capacity += BUFFER_BLOCK_SIZE;
    }

    buffer->data = _realloc(buffer->data, buffer->capacity);
    if (!buffer->data)
        return EXIT_FAILURE;
    memset(buffer->data + buffer->size, 0, buffer->capacity - buffer->size);
    memcpy(buffer->data + buffer->size, data, data_len);
    buffer->size += data_len;

    return EXIT_SUCCESS;
}

int32_t
buffer_append_char(wildcard_buffer_t *buffer, char c)
{
    if (!buffer)
        return EXIT_FAILURE;
    while (buffer->size + 1 >= buffer->capacity) {
        buffer->capacity += BUFFER_BLOCK_SIZE;
    }
    buffer->data = _realloc(buffer->data, buffer->capacity);
    garbage_backup_bucket_ptr(buffer->data);
    if (!buffer->data)
        return EXIT_FAILURE;
    memset(buffer->data + buffer->size, 0, buffer->capacity - buffer->size);
    memcpy(buffer->data + buffer->size, &c, 1);
    buffer->size += 1;
    return EXIT_SUCCESS;
}
