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

void bucket_str_appendf(bucket_str_t *sb, char *format, ...)
{
    va_list args;
    va_start(args, format);
    bucket_str_append_formatted(sb, format, args);
    va_end(args);
}

void bucket_str_print(bucket_str_t *sb)
{
    char *new_bucket = bucket_format(sb);
    int32_t len_new_bucket = _strlen(new_bucket);
    write(1, new_bucket, len_new_bucket);
}

void bucket_str_destroy(bucket_str_t *sb)
{
    free(sb->buffer);
}
