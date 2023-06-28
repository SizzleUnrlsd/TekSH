/*
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
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <dirent.h>
#include <stdio.h>

int32_t
load_and_run_plugin(char *plugin_name, char *function_name, char *command)
{
    void *handle = NULL;
    char *error = NULL;
    plugin_func func;

    handle = dlopen(plugin_name, RTLD_LAZY);
    if (!handle) {
        exit(1);
    }
    dlerror();
    *(void **)(&func) = dlsym(handle, function_name);
    if ((error = dlerror()) != NULL) {
        exit(1);
    }
    plugin_t *plugin = (*func)();
    int32_t rt_ptr_function = -8888;
    if (strcmp(command, plugin->command) == 0) {
        rt_ptr_function = plugin->execute();
    }
    dlclose(handle);
    return rt_ptr_function;
}

char **
get_shared_libraries(const char *dir_path, uint32_t *num_libraries)
{
    DIR *dir;
    struct dirent *entry;
    uint32_t capacity = 10;
    *num_libraries = 0;

    char **libraries = malloc(capacity * sizeof(char *));
    if (!libraries) {
        exit(1);
    }

    if ((dir = opendir(dir_path)) == NULL) {
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        char *name = entry->d_name;
        int len = strlen(name);
        
        if (len > 3 && strcmp(name + len - 3, ".so") == 0) {
            if (*num_libraries == capacity) {
                capacity *= 2;
                libraries = realloc(libraries, sizeof(char *) * capacity);
                if (!libraries) {
                    exit(1);
                }
            }
            libraries[*num_libraries] = malloc(len + 1);
            strcpy(libraries[*num_libraries], name);
            (*num_libraries)++;
        }
    }

    closedir(dir);

    return libraries;
}

char *
concat_str(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* result = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result) {
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

int32_t
loader(shell_t *shell, char **command)
{
    uint32_t lib_index = 0;
    int32_t command_status = 0;
    char **libraries = get_shared_libraries("plugins/add_ons/plugins/", &lib_index);
    if (!libraries)
        return 0;
    for (uint32_t i = 0; i < lib_index; i++) {
        command_status = load_and_run_plugin(concat_str("plugins/add_ons/plugins/", libraries[i]), "init", command[0]);
        if (command_status != -8888)
            break;
        free(libraries[i]);
    }
    free(libraries);
    if (command_status == 0) {
        COMMAND_FOUND;
    }
    return 0;
}