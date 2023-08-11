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

void
remove_quotes(char **str)
{
    int32_t len = _strlen((*str));

    if (len > 1 && *str[0] == '"') {
        (*str)++;
        len--;
    }
    if ((*str)[len - 1] == '"') {
        (*str)[len - 1] = '\0';
    }
}

uint32_t
echo_validity(char *arg)
{
    uint32_t count = DEFAULT(count);

    for (int32_t i = 0; arg[i] != '\0'; i++) {
        if (arg[i] == '"')
            count++;
    }
    return count;
}

int32_t
echo_engine(char **arg, int32_t len_arg, shell_t *shell)
{
    uint32_t tmp = DEFAULT(tmp);

    for (int32_t i = 1; i < len_arg; i++) {
        tmp = tmp + echo_validity(arg[i]);
    }
    if (tmp % 2 != 0) {
        EXIT_W_ECHO_ERROR_("Unmatched '\"'.", 1);
    }
    for (int32_t i = 1; i < len_arg; i++) {
        remove_quotes(&arg[i]);
        print_str(arg[i], 0, 1, 1);
        if (i != len_arg - 1)
            _putchar(' ', 1);
    }
    _putchar('\n', 1);

    return 0;
}

static int32_t
dollar_engine_echo(char **arg, int32_t i, shell_t *shell)
{
    char *tmp = DEFAULT(tmp);

    if (arg[i][0] == '$') {
        if (_strcmp(arg[i], "$?") == 0) {
            _put_nbr(shell->status);
            _putchar('\n', 1);
            return 0;
        }
        if (_strcmp(arg[i], "$?") != 0) {
            tmp = getenv(arg[i] + 1);
        }
    }
    if (tmp == NULL) {
        _putstr(arg[i] + 1, 2);
        EXIT_W_ECHO_ERROR_(": Undefined variable.", 1);
    } else {
        pfflush_wrapper(1, "%s\n", tmp);
    }

    return 0;
}

int32_t
_echo(shell_t *shell)
{
    char **arg = parse_stdin(shell->line);
    int32_t len_arg = len_array(arg);

    COMMAND_FOUND;

    if (len_arg == 1) {
        print_str("\n", 0, 1, 1);
        UPDATE_SUCCESS_STATUS;
        return 0;
    }
    if (len_arg > 1 && _strncmp(arg[1], "$", 1) == 0) {
        for (int32_t i = 1; i < len_arg; i++)
            dollar_engine_echo(arg, i, shell);
    }
    if (len_arg > 1 && _strncmp(arg[1], "$", 1) != 0) {
        shell->status = echo_engine(arg, len_arg, shell);
        return 0;
    }
    UPDATE_SUCCESS_STATUS;
    return 0;
}
