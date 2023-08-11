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

char *
getgit_branch()
{
    char _buf[128] = {0};
    char *branch = NULL;
    char *tmp = NULL;
    size_t len = DEFAULT(len);
    FILE *fp = fopen(".git/HEAD", "r");
    if (!fp) {
        return "UNDEFINE";
    }

    if (fgets(_buf, sizeof(_buf), fp) != NULL) {
        if (strncmp(_buf, "ref: refs/heads/", 16) == 0) {
            branch = _buf + 16;
            len = strlen(branch);
            (len > 0 && branch[len - 1] == '\n') ? branch[len - 1] = '\0' : 0;
        } else {
            _print("NONE");
        }
    }
    fclose(fp);
    tmp = strdup(branch);
    garbage_backup_ptr(tmp);
    return tmp;
}
