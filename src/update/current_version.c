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
handleVersion(void)
{
    const char *filename = "setup/shell.conf";
    char *current_version = NULL;
    FILE *file = fopen(filename, "r");
    if (!file) {
        exit(!!_FILE_ERROR);
    }

    char line[256];
    while (fgets(line, 256, file) != NULL) {
        if (strstr(line, "version =") != NULL) {
            current_version = strchr(line, '=');
            if (current_version != NULL) {
                current_version++;
                while (*current_version == ' ' || *current_version == '\t') {
                    current_version++;
                }
                current_version[strcspn(current_version, "\r\n")] = '\0';
                break;
            }
        }
    }
    fclose(file);
    char const *_buf =
                "████████╗███████╗██╗  ██╗███████╗██╗  ██╗\n"
                "╚══██╔══╝██╔════╝██║ ██╔╝██╔════╝██║  ██║\n"
                "   ██║   █████╗  █████╔╝ ███████╗███████║\n"
                "   ██║   ██╔══╝  ██╔═██╗ ╚════██║██╔══██║\n"
                "   ██║   ███████╗██║  ██╗███████║██║  ██║\n"
                "   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n";

    _print(_CLEAR_TERM);
    _printf("%s", _buf);
    _printf("%s\n", current_version);
    exit(EXIT_SUCCESS);
}
