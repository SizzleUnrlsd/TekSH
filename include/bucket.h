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

#ifndef BUCKET_H_
    #define BUCKET_H_
    #include "shell.h"

    #define BUCKET_SIZE 1024

    typedef struct bucket_str_s {
        char *buffer;
        size_t used;
        size_t size;
    } bucket_str_t;

    bucket_str_t *bucket_str_init(void);
    char *bucket_format(bucket_str_t *sb);
    void bucket_str_print(bucket_str_t *sb);
    void bucket_str_destroy(bucket_str_t *sb);
    void bucket_str_append(bucket_str_t *sb, char *str);
    void bucket_str_append_int(bucket_str_t *sb, int value);
    void bucket_str_appendf(bucket_str_t *sb, char *format, ...);
    void bucket_str_append_formatted(bucket_str_t *sb,
    char *format, va_list args);

#endif /* !BUCKET_H_ */
