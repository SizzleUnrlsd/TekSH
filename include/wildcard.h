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

#ifndef _WILDCARD_H_
    #define _WILDCARD_H_

    #define BUFFER_BLOCK_SIZE 8

    #include <stdlib.h>

typedef struct wildcard_buffer_s {
    char *data;
    size_t size;
    size_t capacity;
} wildcard_buffer_t;

wildcard_buffer_t *init_buffer(void);
void terminate_buffer(wildcard_buffer_t *buffer);
int buffer_append(wildcard_buffer_t *buffer, char *data);
int buffer_append_char(wildcard_buffer_t *buffer, char c);
char *buffer_get_data(wildcard_buffer_t *buffer);
size_t buffer_get_size(wildcard_buffer_t *buffer);
void buffer_clear(wildcard_buffer_t *buffer);
void buffer_back_cursor(wildcard_buffer_t *buffer, size_t cursor);

typedef struct wildcard_s {
    char *command;
    char *pwd;
    char **file_list;
    wildcard_buffer_t *new_command;
} wildcard_t;

typedef struct wildcard_convert_s {
    size_t old_last_space_index;
    size_t last_space_index;
    size_t next_space_index;
    char *format;
    char *converted_format;
    char *word_array;
} wildcard_convert_t;

char *update_wildcard(char *command, shell_t *shell);
wildcard_t *init_wildcard(char *command);
void terminate_wildcard(wildcard_t *wildcard);
char **wildcard_list_files(char *pwd);
int wildcard_convert(wildcard_t *wildcard);
char *wildcard_transform(wildcard_t *wildcard, char *format);

size_t get_last_space_index(char *command, size_t index);
size_t get_next_space_index(char *command, size_t index);
char *wildcard_get_sub_string(char *str, size_t start, size_t end);
char *convert_str_to_format(char *str);

#endif
