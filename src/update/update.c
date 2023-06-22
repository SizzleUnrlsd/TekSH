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

char *get_readme_from_github(const char* repo_owner, const char* repo_name)
{
    const char* base_url = "https://raw.githubusercontent.com";
    const char* endpoint = "/%s/%s/main/README.md";

    char _buf[128] = {0};
    char _buf_url[256] = {0};
    char _buf_command[512] = {0};
    char *output = NULL;
    size_t output_size = 0;
    size_t buffer_size = 0;

    snprintf(_buf_url, sizeof(_buf_url), endpoint, repo_owner, repo_name);
    snprintf(_buf_command, sizeof(_buf_command), "curl -s %s%s", base_url, _buf_url);

    FILE* fp = popen(_buf_command, "r");
    if (!fp) {
        return NULL;
    }

    while ((buffer_size = fread(_buf, 1, sizeof(_buf), fp)) > 0) {
        output = realloc(output, output_size + buffer_size + 1);
        memcpy(output + output_size, _buf, buffer_size);
        output_size += buffer_size;
    }
    pclose(fp);

    if (output_size == 0) {
        return NULL;
    }
    output[output_size] = '\0';

    return output;
}


const char *
find_version(const char *_buf)
{
    const char *version = NULL;
    const char *keyword = "Version";

    version = strstr(_buf, keyword);
    if (version != NULL) {
        version += strlen(keyword);
        while (*version == ' ' || *version == '\t') {
            version++;
        }
        return version;
    }

    return NULL;
}

void
update_services(void)
{
    char const *_buf =
                "████████╗███████╗██╗  ██╗███████╗██╗  ██╗\n"
                "╚══██╔══╝██╔════╝██║ ██╔╝██╔════╝██║  ██║\n"
                "   ██║   █████╗  █████╔╝ ███████╗███████║\n"
                "   ██║   ██╔══╝  ██╔═██╗ ╚════██║██╔══██║\n"
                "   ██║   ███████╗██║  ██╗███████║██║  ██║\n"
                "   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝\n";

    _print(_CLEAR_TERM);
    _printf("%s", _buf);
    _print("You're not up to date,\n\
Update to the latest version? Y / n\n");

    char *input = readline("$> ");
    if (!input || !*input) {
        return;
    }

    if (input[0] == 'Y' || input[0] == 'y') {
        _print("Please refer to the following link 'https://github.com/SizzleUnrlsd/TekSH'. \
Automatic updates available soon.\n");
    } else {
        _print("Update canceled.\n");
    }

    free(input);
}

int
check_current_version(const char *version)
{
    const char *filename = "setup/shell.conf";

    FILE *file = fopen(filename, "r");
    if (!file) {
        return !_FILE_ERROR;
    }

    char line[256];
    while (fgets(line, 256, file) != NULL) {
        if (strstr(line, "version =") != NULL) {
            char *current_version = strchr(line, '=');
            if (current_version != NULL) {
                current_version++;
                while (*current_version == ' ' || *current_version == '\t') {
                    current_version++;
                }
                current_version[strcspn(current_version, "\r\n")] = '\0';

                int32_t result = strncmp(current_version, version, 5);
                if (result == 0) {
                    return 0;
                } else {
                    return 1;
                }
                break;
            }
        }
    }
    fclose(file);

    return 0;
}

int check_version(void)
{
    const char *version = NULL;
    char *readme = get_readme_from_github("SizzleUnrlsd", "TekSH");

    if (!readme){
        return !!_BUF_ERROR;
    }
    version = find_version(readme);
    if (!version) {
        return !!_CONST_BUF_ERROR;
    }
    if (check_current_version(version)) {
        update_services();
    }

    return 0;
}
