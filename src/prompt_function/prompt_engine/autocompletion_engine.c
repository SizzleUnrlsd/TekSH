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
#include <termios.h>
#include <sys/ioctl.h>

#define RESET_TERM  "\x1B[0m"
#define BOLD_GREEN  "\x1B[1;32m"
#define BOLD_BLUE   "\x1B[1;34m"

char *make_list[] = {
    "fclean",
    "re",
    "clean",
    "all",
    NULL
};

char *git_list[] = {
    "add",
    "branch",
    "checkout",
    "clone",
    "commit",
    "diff",
    "fetch",
    "init",
    "log",
    "merge",
    "pull",
    "push",
    "rebase",
    "status",
    NULL
};

char *docker_list[] = {
    "build",
    "compose",
    NULL
};

char *command_list[] = {
    "make",
    "git",
    "docker",
    NULL
};

typedef struct {
    const char *command;
    char **list;
} command_t;

command_t commands[] = {
    { "make", make_list },
    { "git", git_list },
    { "docker", docker_list },
    { NULL, NULL }
};

char **current_list;

bool printable = false;

int is_directory(const char *filename) {
    struct stat path_stat;
    if (stat(filename, &path_stat) == 0) {
        return S_ISDIR(path_stat.st_mode);
    }
    return 0;
}

int is_executable(const char *filename) {
    struct stat path_stat;
    if (stat(filename, &path_stat) == 0) {
        return !S_ISDIR(path_stat.st_mode) && ((path_stat.st_mode & S_IXUSR) || (path_stat.st_mode & S_IXGRP) || (path_stat.st_mode & S_IXOTH));
    }
    return 0;
}

int format_output(char **str, int len_array)
{
    int num_files = len_array;
    int win_width = 0;
    int largest_str = 0;
    int num_columns = 0;
    int num_rows = 0;
    char *filename = NULL;
    char *color_code = NULL;
    int len_prompt = 0;

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    win_width = w.ws_col;

    if (strcmp("UNDEFINE", getgit_branch()) == 0) {
        len_prompt = rl_point;
    } else {
        len_prompt = rl_point + (_strlen(getgit_branch()) * 8);
    }

    largest_str = 0;
    for (int i = 0; i < num_files; i++) {
        int len = strlen(str[i]);
        if (len > largest_str)
            largest_str = len;
    }

    num_columns = (win_width / (largest_str + 1));
    num_rows = ((num_files + num_columns - 1) / num_columns);

    if (printable == false) {
        for (int i = 0; i < len_prompt + 1; i++) {
            _print(" ");
        }
    }

    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_columns; col++) {
            int index = col * num_rows + row;
            if (index >= num_files)
                break;

            filename = str[index];
            color_code = RESET_TERM;

            if (is_directory(filename) != 0) {
                color_code = BOLD_BLUE;
            }
            if (is_executable(filename) != 0) {
                color_code = BOLD_GREEN;
            }
            _printf("%s%-*s%s", color_code, largest_str + 1, filename, RESET_TERM);
        }
        _print("\n");
    }
    return 0;
}

char *completion_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = current_list[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }
    return NULL;
}

char **command_completion(const char *text, int start, int end UNUSED_ARG)
{
    char **matches = NULL;
    char *first_space = NULL;

    if (text[0] == '\0' && end == 0) {
        return NULL;
    }

    if (start == 0 || rl_line_buffer[start - 1] == '(' || rl_line_buffer[start - 1] == ';' ||
        rl_line_buffer[start - 1] == '|' || rl_line_buffer[start - 1] == '&' ||
        rl_line_buffer[start - 1] == '>' || rl_line_buffer[start - 1] == '<') {
        current_list = command_list;
    } else {
        char *command_start = rl_line_buffer;
        for (char *p = &rl_line_buffer[start - 1]; p != rl_line_buffer; p--) {
            if (*p == '(' || *p == ';' || *p == '|' || *p == '&' || *p == '>' || *p == '<') {
                command_start = p + 1;
                break;
            }
        }

        while (*command_start == ' ') command_start++;

        if (command_start == &rl_line_buffer[start]) {
            current_list = command_list;
        } else {
            size_t length = strlen(command_start);
            char command[length + 1];
            strncpy(command, command_start, length);
            command[length] = '\0';

            first_space = strchr(command, ' ');
            if (first_space != NULL) {
                *first_space = '\0';
            }

            for (int i = 0; commands[i].command; i++) {
                if (strcmp(command, commands[i].command) == 0) {
                    current_list = commands[i].list;
                    break;
                }
                current_list = NULL;
            }
        }
    }

    if (current_list != NULL) {
        matches = rl_completion_matches(text, completion_generator);
    }
    if (matches == NULL)
        printable = true;
    else
        printable = false;
    return matches;
}

void my_completion_display_matches(char **matches, int num_matches UNUSED_ARG, int max_length UNUSED_ARG)
{
    static int a = 0;
    int len_array_var = 0;
    static char *first_comp = NULL;
    static char *last_comp = NULL;

    if (rl_line_buffer[0] == '\0') {
        return;
    }

    if (( a%2 ) == 0 && first_comp == NULL && last_comp == NULL) {
        first_comp = strdup(rl_line_buffer);
        ++a;
        goto looser;
    }
    
    if (( a%2 ) != 0 && first_comp != NULL) {
        last_comp = rl_line_buffer;
        ++a;
    }

    if (strcmp(first_comp, rl_line_buffer) == 0) {
        return;
    } else {
        first_comp = NULL;
        last_comp = NULL;
        a = 0;
    }
    
looser:

    rl_attempted_completion_function = command_completion;
    for (int i = 0; matches[i]; i++) {
        len_array_var++;
    }

    rl_crlf();
    format_output(matches, len_array_var);
    rl_already_prompted = 0;
    rl_forced_update_display();
}
