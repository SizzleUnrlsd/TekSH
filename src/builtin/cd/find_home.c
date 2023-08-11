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

static char *
second_chance(shell_t *shell UNUSED_ARG)
{
    struct passwd *pw = getpwuid(getuid());
    if (pw != NULL && pw->pw_dir != NULL) {
        return _strdup(pw->pw_dir);
    } else {
        return NULL;
    }
}

char *
find_home(shell_t *shell, char *home)
{
    char **first_step = DEFAULT(first_step);
    char **env = shell->set_env->env_array;

    for (int32_t i = 0; env[i]; i++) {
        first_step = _str_to_word_array_custom(env[i], '=');
        if (_strcmp(first_step[0], "HOME") == 0) {
            home = _strdup(first_step[1]);
            return home;
        }
    }
    return second_chance(shell);
}
