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

char *
getgit_branch()
{
    char _buf[128] = {0};
    char *branch = NULL;
    FILE *fp = fopen(".git/HEAD", "r");
    if (!fp) {
        return "UNDEFINE";
    }

    if (fgets(_buf, sizeof(_buf), fp) != NULL) {
        if (strncmp(_buf, "ref: refs/heads/", 16) == 0) {
            branch = _buf + 16;
            size_t len = strlen(branch);
            (len > 0 && branch[len - 1] == '\n') ? branch[len - 1] = '\0' : 0;
        } else {
            _print("NONE");
        }
    }
    fclose(fp);

    return strdup(branch);
}
