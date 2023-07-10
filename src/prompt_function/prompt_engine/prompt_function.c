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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

void
switch_sig(shell_t *shell, int32_t wstatus)
{
    if (wstatus == 256)
        shell->status = 1;
    else
        shell->status = wstatus;
    if (WIFSIGNALED(wstatus)) {
        if (WTERMSIG(wstatus) == SIGABRT)
            print_str("Abort", 0, true, 2);
        if (WTERMSIG(wstatus) == SIGBUS)
            print_str("Bus error", 0, true, 2);
        if (WTERMSIG(wstatus) == SIGFPE)
            print_str("Floating exception", 0, true, 2);
        if (WTERMSIG(wstatus) == SIGSEGV)
            print_str("Segmentation fault", 0, true, 2);
        if (WCOREDUMP(wstatus))
            print_str(" (core dumped)", '\n', true, 2);
    }
    return;
}

int32_t
prompt_function(shell_t *shell, set_env_t *env_set, char **arg)
{
    int32_t wstatus = DEFAULT(wstatus);
    pid_t pid = fork();

    if (pid == -1)
        return 84;
    if (pid == 0) {
        if (arg == NULL) {
            _exit(0);
        }
        if (open_directory(shell, env_set->path_env, arg) == 1) {
            _exit(shell->status);
        }
        if (access_file(shell, arg) == 1) {
            shell->status = 1;
        }
        _exit(shell->status);
    }
    if (pid != 0) {
        waitpid(pid, &wstatus, 0);
        switch_sig(shell, wstatus);
        parent_exit(shell, wstatus);
    }
    shell->command_not_found = 0;
    return 0;
}
