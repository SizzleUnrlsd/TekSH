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

volatile sig_atomic_t interrupt_flag = DEFAULT(interrupt_flag);

static volatile sig_atomic_t keep_running = 1;

static bool _tty = false;

char *detail = NULL;

int load_history(const char *filename)
{
    return read_history(filename);
}

int save_history(const char *filename)
{
    return write_history(filename);
}

char **command_completion(const char *text, int start, int end)
{
    (void) start;
    (void) end;
    return rl_completion_matches(text, rl_filename_completion_function);
}

char *
get_dir(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        return strdup(cwd);
    } else {
        return "UNDEFINE";
    }

    return 0;
}

static char *concat_str(const char *str1, const char *str2, ...)
{
    va_list args;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    const char *str = DEFAULT(str);

    char *result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result) {
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);

    va_start(args, str2);
    
    while ((str = va_arg(args, const char *)) != NULL) {
        size_t len = strlen(str);
        result = (char *)realloc(result, sizeof(char) * (len1 + len2 + len + 1));
        if (!result) {
            exit(EXIT_FAILURE);
        }
        strcat(result, str);
        len1 += len;
    }
    va_end(args);

    return result;
}

/* Prompt design */
char *set_promt(void)
{
    char prompt[512] = {0};
    char *_detail = DEFAULT(_detail);
    char *reset = "\033[0m";
    char start = '{';
    char end = '}';

    if (strcmp("UNDEFINE", getgit_branch()) != 0)
        sprintf(prompt, "\033[1;34m%c \033[1;31m%s\033[0m \033[1;34m%c %s", start, getgit_branch(), end, reset);
    else
        sprintf(prompt, " ");

    _detail = concat_str("\033[0;34m[", reset, get_dir(), "\033[0;34m]", reset, prompt, NULL);
    return strdup(_detail);
}

/* Sigint management */
void inthand(int32_t signum UNUSED_ARG)
{
    if (_tty) {
        /* Handles the case where the prompt buffer is full */
        rl_replace_line("", 0);
        rl_redisplay();
        _print("\n");
        _print(ANSI_BOLD_ON);
        _print(ANSI_COLOR_BLUE "•" ANSI_COLOR_RESET);
        _print(detail);
        fflush(stdout);
        rl_cleanup_after_signal();
    }
}

int32_t prompt_shell(shell_t *shell)
{
    char *line = DEFAULT(line);
    static int32_t first_call = 1;
    struct termios old_termios, new_termios;

    /* If the shell is not in tty mode, use getline() */
    size_t len = DEFAULT(len);
    ssize_t read;

    static int32_t screen_height = DEFAULT(screen_height), screen_width = DEFAULT(screen_width);
    rl_get_screen_size(&screen_height, &screen_width);
    rl_set_screen_size(1000, screen_height);

    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;
    new_termios.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    _tty = shell->print;

    signal(SIGINT, inthand);
    if (first_call) {
        rl_extend_line_buffer(1024);
        first_call = 0;
        load_history("history.txt");
        rl_attempted_completion_function = command_completion;
    }
    
    detail = set_promt();
    if (!detail) {
        _p_error(_MEM_ALLOCA_ERROR);
    }
    garbage_collector(detail, shell);

    do {
        if (shell->status == 0 && RD_TTY) {
            _print(ANSI_BOLD_ON);
            _print(ANSI_COLOR_BLUE "•" ANSI_COLOR_RESET);
        } else if (shell->status != 0 && RD_TTY) {
            _print(ANSI_BOLD_ON);
            _print(ANSI_COLOR_RED "•" ANSI_COLOR_RESET);
        }

        /* Not in the tty*/
        if (!_tty) {
            read = getline(&line, &len, stdin);
        }
        if (read == -1) {
            exit(shell->status);
        }

        /* In the tty */
        if (_tty) {
            line = readline(detail);
        }
        if (!line) {
            return 42;
        }

        garbage_collector(line, shell);
        if (errno == EINTR) {
            continue;
        }
        if (strcmp(line, "\0") == 0) {
            shell->status = 0;
            continue;
        }
        if (line && *line) {
            add_history(line);
            shell->get_line = line;
            ENV_PATH = cut_path_env(shell, ENV_SET_ARRAY);
            save_history("history.txt");
        } else if (line) {
            print_str(detail, 0, RD_TTY, 1);
        }
    } while (!line || !*line);

    return 0;
}
