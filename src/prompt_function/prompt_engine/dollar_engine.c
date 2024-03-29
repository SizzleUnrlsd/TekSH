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

int32_t
dollar_engine(char **arg, int32_t i, shell_t *shell)
{
    char *tmp = NULL;

    if (arg[i][0] == '$') {
        if (_strcmp(arg[i], "$?") == 0) {
            _printfe("%d", shell->status);
            EXIT_W_ECHO_ERROR_(": Command not found.", 1);
            return 0;
        }
        if (_strcmp(arg[i], "$?") != 0)
            tmp = getenv(arg[i] + 1);
    }
    if (tmp == NULL && arg[i][0] == '$') {
        _putstr(arg[i] + 1, 2);
        EXIT_W_ECHO_ERROR_(": Undefined variable.", 1);
    } else if (check_perm_dollar_engine(arg[i] + 1, tmp, shell) != 0) {
        return 1;
    } else {
        _printf("%s", tmp);
        EXIT_W_ECHO_ERROR_(": Command not found.", 1);
    }
    return 0;
}
