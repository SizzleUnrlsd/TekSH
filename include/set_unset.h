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

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>

#include "./shell.h"

typedef struct shell_local_s {
    char **m_cmds;
    char **env;
    char **cmd;
    char **local_env;
    char *param;
    char *value;
    char *name;
    char *str;
    char *tmp;
    char *one_cmd;
    size_t len;
} shell_local_t;

char **mstwa(char *str, char const *sep);
char *my_strconcat(char *src_left, char *src_right);
int is_input_valid(char *name, shell_local_t *shell);
int check_malloc(char **new_env, char *n_key);
int find_symbol(char *str, char symbol);
int search_existing_var(shell_local_t *shell);
int cd_ext_ext(shell_local_t *shell, int i);
int loop_condition(shell_local_t *shell);
int execute_this(shell_local_t *shell);
int my_unsetenv(shell_local_t *shell);
int my_getnbr(char const *str);
int my_setenv(shell_local_t *shell);
int my_unset(shell_t *shell);
int check_setenv(shell_t *shell, char *name);
int all_bin(shell_local_t *shell);
int my_exit(shell_local_t *shell);
int my_envlen(char **array);
int my_env(shell_local_t *shell);
int my_set(shell_t *shell);
int check_char_num(char c);
int my_cd(shell_local_t *shell);
int check_set(shell_t *shell, char *name);
int my_error(char *str);
int my_isalnum(char c);
int not_dir(char *str);
int perm(char *str);
void init_local_env(shell_t *shell);
void my_putstr_error(char *str);
void free_array(char **array);
void get_path(shell_local_t *shell);
void my_putchar_error(char c);
void siginit(int pid);
