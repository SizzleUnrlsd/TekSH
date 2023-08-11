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

static void
replace_substr(char *str, const char *substr, const char *replacement)
{
    char *found = strstr(str, substr);

    if (found != NULL) {
        size_t substrLen = strlen(substr);
        size_t replacementLen = strlen(replacement);
        memmove(found + replacementLen, found + substrLen, strlen(found + substrLen) + 1);
        memcpy(found, replacement, replacementLen);
    }
}

char *
get_dir(void)
{
    char cwd[1024] = {0};

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        replace_substr(cwd, get_home(), "~");
        if (strlen(cwd) == 1)
            return _strdup(strcat(cwd, "/"));
        return _strdup(cwd);
    } else {
        return "UNDEFINE";
    }

    return 0;
}
