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
free_ptr(char **arg)
{
    for (int32_t i = 0; arg[i]; i++) {
        free(arg[i]);
        arg[i] = NULL;
    }
    return;
}

char *
add_space_after_exclamation(char *buf)
{
    int32_t i = 0, j = 0, count = 0;
    int32_t len = _strlen(buf);
    char *new_buf = DEFAULT(new_buf);

    for (i = 0; i < len; i++) {
        if (buf[i] == '!')
            count++;
    }
    new_buf = malloc(len + count + 1);
    if (!new_buf) {
        _p_error(_MEM_ALLOCA_ERROR);
    }

    for (i = 0, j = 0; i < len; i++, j++) {
        new_buf[j] = buf[i];
        if (buf[i] == '!') {
            j++;
            new_buf[j] = ' ';
        }
    }
    new_buf[j] = '\0';
    return new_buf;
}

void
little_inibitor(char **command)
{
    if ((*command)[0] == 92)
        (*command)++;
    return;
}

char **
parse_stdin(char *command, shell_t *shell)
{
    char **clean_arg = DEFAULT(clean_arg), **arg = DEFAULT(arg);
    int32_t a = DEFAULT(a), count = DEFAULT(count);

    little_inibitor(&command);
    if (command[0] == '!')
        command = add_space_after_exclamation(command);
    arg = _str_to_word_array_custom_double(shell, command, ' ', '\t');
    for (int32_t i = 0; arg[i]; i++)
        if ((_strcmp(arg[i], " ") != 0) || (_strcmp(arg[i], "\t") != 0))
            a++;
    clean_arg = (char **)malloc_attribut(sizeof(char *) * (a + 1), shell);
    for (int32_t i = 0; arg[i]; i++) {
        if ((_strcmp(arg[i], " ") != 0) || (_strcmp(arg[i], "\t") != 0)) {
            clean_arg[count] = _strdup(arg[i], shell);
            count++;
        }
    }
    clean_arg[a] = NULL;
    free_ptr(arg);
    arg = NULL;
    return clean_arg;
}
