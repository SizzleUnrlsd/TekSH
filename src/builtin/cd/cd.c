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
set_new_old_pwd(shell_t *shell, char *path, char *mess_env)
{
    int32_t fmall = _strlen(path);
    char *concat = NULL;
    char *final = NULL;
    char **diff = NULL;

    free_attribut(shell->get_line, shell);
    concat = concat_char_str(' ', mess_env, fmall, 1);
    garbage_collector(concat, shell);
    final = _strcat(concat, path);
    final = concat_char_str('\n', final, 1, 1);
    shell->get_line = final;

    diff = _str_to_word_array_custom(shell, mess_env, ' ');

    if (pwd_already_ini_env(shell, diff[1]) == 1)
        add_line_to_array(shell, 3, 0);
    else
        add_line_to_array(shell, 3, -3);

    return;
}

int32_t
build_cd_foo_extend(shell_t *shell, char **arg, char *home, int32_t len_arg)
{
    if (check_perm_dir(shell, home, 0) == 1)
        return 1;
    if ((home != NULL && len_arg == 1) ||
    ((_strcmp(arg[1], "~") == 0) && home != NULL)) {
        shell->cd_old_path = getcwd(NULL, 4096);
        garbage_collector(shell->cd_old_path, shell);
        if (chdir(home) == -1) {
            EXIT_W_ECHO_ERROR_("cd: Can't change to home directory.", 1);
        }
        shell->cd_new_path = home;
        set_new_old_pwd(shell, shell->cd_old_path, "setenv OLDPWD");
        set_new_old_pwd(shell, home, "setenv PWD");
        return 1;
    }
    return 0;
}

int32_t
build_cd_foo(shell_t *shell, char *home, char **arg, int32_t len_arg)
{
    struct stat st;
    home = find_home(shell, home);
    if (stat(home, &st) == -1 && len_arg == 1) {
        EXIT_W_ECHO_ERROR_("cd: Can't change to home directory.", 1);
    }
    if ((home == NULL && len_arg == 2 && _strcmp(arg[1], "~") == 0)) {
        EXIT_W_ECHO_ERROR_("No $home variable set.", 1);
    }
    if (stat(home, &st) == -1 && len_arg == 2 && _strcmp(arg[1], "~") == 0) {
        print_str(home, 0, true, 2);
        EXIT_W_ECHO_ERROR_(": No such file or directory.", 1);
    }
    if ((home == NULL && len_arg == 1)) {
        EXIT_W_ECHO_ERROR_("cd: No home directory.", 1);
    }
    if (home != NULL && build_cd_foo_extend(shell, arg, home, len_arg) == 1)
        return 1;
    return 0;
}

int32_t
build_cd_bar(shell_t *shell, char **arg)
{
    if (_strcmp(arg[1], "-") == 0) {
        if (shell->cd_old_path == NULL && shell->cd_new_path == NULL) {
            EXIT_W_ECHO_ERROR_(": No such file or directory.", 1);
        } else {
            char *path = getcwd(NULL, 4096);
            garbage_collector(path, shell);
            set_new_old_pwd(shell, path, "setenv OLDPWD");
            if (chdir(shell->cd_old_path) == -1) {
                EXIT_W_ECHO_ERROR_("chdir: Error.", 1);
            }
            shell->cd_old_path = shell->cd_new_path;
            shell->cd_new_path = getcwd(NULL, 4096);
            garbage_collector(shell->cd_new_path, shell);
            set_new_old_pwd(shell, shell->cd_new_path, "setenv PWD");
        }
        return 1;
    }
    return 0;
}

int32_t
build_cd_foobar(shell_t *shell, char **arg,
    int32_t len_arg, uint32_t *invalid_cd)
{
    int32_t result = 0;

    if (len_arg == 2 && check_perm_dir(shell, arg[1], invalid_cd) == 0) {
        shell->cd_old_path = getcwd(NULL, 4096);
        garbage_collector(shell->cd_old_path, shell);
        set_new_old_pwd(shell, shell->cd_old_path, "setenv OLDPWD");
        result = chdir(arg[1]);
        shell->cd_new_path = getcwd(NULL, 4096);
        garbage_collector(shell->cd_new_path, shell);
        set_new_old_pwd(shell, shell->cd_new_path, "setenv PWD");
        if (is_dir(arg[1]) == 1) {
            print_str(arg[1], 0, true, 2);
            EXIT_W_ECHO_ERROR_(": Not a directory.", 1);
        }
        if (result == -1) {
            print_str(arg[1], 0, true, 2);
            EXIT_W_ECHO_ERROR_(": No such file or directory.", 1);
        }
        return 1;
    }
    return 0;
}
