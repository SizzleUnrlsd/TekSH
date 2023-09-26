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
bool current_process = false;
char *detail = DEFAULT(detail);
char _gbuf[256] = {0};
shell_t *_gshell;

uint64_t count_readline;

int load_history(const char *filename)
{
    return read_history(filename);
}

int save_history(const char *filename)
{
    return write_history(filename);
}

static char *
concat_str(const char *str1, const char *str2, ...)
{
    va_list args;
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    const char *str = DEFAULT(str);

    char *result = (char *)_mallocbucket(sizeof(char) * (len1 + len2 + 1));
    if (!result) {
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    strcat(result, str2);

    va_start(args, str2);
    
    while ((str = va_arg(args, const char *)) != NULL) {
        size_t len = strlen(str);
        result = (char *)_realloc(result, sizeof(char) * (len1 + len2 + len + 1));
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
    char start = '[';
    char end = ']';

    if (strcmp("UNDEFINED", getgit_branch()) != 0)
        sprintf(prompt, "\033[0;34m%c\033[1;31m%s\033[0m\033[0;34m%c %s", start, getgit_branch(), end, reset);
    else
        sprintf(prompt, " ");

    _detail = concat_str("\033[0;34m[", reset, get_dir(), "\033[0;34m]", reset, prompt, NULL);
    garbage_backup_ptr(_detail);
    return _strdup(_detail);
}

/* Sigint management */
void inthand(int32_t signum UNUSED_ARG)
{
    char _buf[256] = {0};
    sprintf(_buf, "%s%s%s", "\x1b[1m", ANSI_COLOR_BLUE "•" ANSI_COLOR_RESET, detail);

    if (signum == SIGINT && _tty && current_process == false) {
        /* Handles the case where the prompt buffer is full */
        count_readline++;
        rl_free_line_state();
        rl_replace_line("", 0);
        rl_crlf();
        rl_redisplay();
        _printf("%s", _buf);
        rl_cleanup_after_signal();
    }
    if (signum == SIGTSTP) {
        rl_forced_update_display();
        return;
    }
}

_wur int32_t
prompt_shell(shell_t *shell)
{
    static char historyFilePath[256] = {0};
    char *line = DEFAULT(line);
    static int32_t first_call = true;
    struct termios old_termios, new_termios;

    /* If the shell is not in tty mode, use getline() */
    size_t len = DEFAULT(len);
    ssize_t read = DEFAULT(read);

    static int32_t screen_height = DEFAULT(screen_height), screen_width = DEFAULT(screen_width);

    if (shell->print && (screen_height == 0 || screen_width == 0)) {
        rl_get_screen_size(&screen_height, &screen_width);
        rl_set_screen_size(1000, screen_height);

        tcgetattr(STDIN_FILENO, &old_termios);
        new_termios = old_termios;
        new_termios.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    }


    _tty = shell->print;
    _gshell = shell;

    signal(SIGINT, inthand);
    signal(SIGTSTP, inthand);

    if (first_call) {
        /* The 'rl_initialize()' function must be called once before the first call to readline.
            Otherwise it may cause problems with the display of the prompt.
            In addition, its presence is necessary to avoid initialization memory errors. */
        rl_initialize();
        rl_extend_line_buffer(1024);
        first_call = false;
        snprintf(historyFilePath, sizeof(historyFilePath), "%s/TekShistory.txt", get_home());
        load_history(historyFilePath);
        rl_attempted_completion_function = command_completion;
    }
    
    detail = set_promt();
    if (!detail) {
        _p_error(_MEM_ALLOCA_ERROR);
    }

    do {
        if (shell->status == 0 && RD_TTY) {
            sprintf(_gbuf, "%s%s%s", "\x1b[1m", ANSI_COLOR_BLUE "•" ANSI_COLOR_RESET, detail);
        } else if (shell->status != 0 && RD_TTY) {
            sprintf(_gbuf, "%s%s%s", "\x1b[1m", ANSI_COLOR_RED "•" ANSI_COLOR_RESET, detail);
        }

        /* Not in the tty*/
        if (!_tty) {
            if (getline(&line, &len, stdin) == -1) {
                exit(shell->status);
            }
            if (strcmp(line, "\n") == 0)
                exit(shell->status);
            garbage_backup_ptr((void*)line);
        }
        /* In the tty */
        if (_tty) {
            rl_bind_key(12, clear_wrapper);
            rl_completion_display_matches_hook = my_completion_display_matches;
            if (line = readline(_gbuf), !line) {
                return 42;
            }
            garbage_backup_ptr((void*)line);
            count_readline++;
        }

        if (errno == EINTR) {
            continue;
        }
        if (strcmp(line, "\0") == 0) {
            shell->status = 0;
            continue;
        }
        if (line && *line) {
            add_history(line);
            shell->line = line;
            ENV_PATH = cut_path_env(ENV_SET_ARRAY);
            save_history(historyFilePath);
        } else if (line) {
            print_str(detail, 0, RD_TTY, 1);
        }
    } while (!line || !*line);

    return 0;
}
