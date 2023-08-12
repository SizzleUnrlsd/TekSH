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

char *getgit_branch(void)
{
    char _buf[128] = {0};
    char *branch = DEFAULT(branch);
    size_t len = sizeof(_buf);
    FILE *fp = popen("git name-rev --name-only HEAD 2>/dev/null", "r");

    if (!fp) {
        return "UNDEFINED";
    }

    if (fgets(_buf, sizeof(_buf), fp) != NULL) {
        len = strlen(_buf);
        if (len > 0 && _buf[len - 1] == '\n') {
            _buf[len - 1] = '\0';
        }
        branch = strdup(_buf);
    } else {
        branch = strdup("UNDEFINED");
    }

    pclose(fp);

    if (!branch)
        return "UNDEFINED";

    garbage_backup_ptr(branch);
    return branch;
}
