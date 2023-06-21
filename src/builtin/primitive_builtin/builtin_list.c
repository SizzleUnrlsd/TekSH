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

int32_t
builtin_exit(shell_t *shell)
{
    COMMAND_FOUND;
    char **arg = parse_stdin(shell->get_line, shell);
    int32_t len_arg = len_array(arg);
    exit_error(shell, arg, len_arg);
    return 1;
}

int32_t
builtin_cd(shell_t *shell)
{
    COMMAND_FOUND;
    char *home = NULL;
    uint32_t invalid_cd = 0;
    char **arg = parse_stdin(shell->get_line, shell);
    int32_t len_arg = len_array(parse_stdin(shell->get_line, shell));
    if (build_cd_foo(shell, home, arg, len_arg) == 1) {
        invalid_cd++;
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (build_cd_bar(shell, arg) == 1) {
        invalid_cd++;
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (build_cd_foobar(shell, arg, len_arg, &invalid_cd) == 1) return 0;
    if (invalid_cd == 0) {
        EXIT_W_ECHO_ERROR_("cd: Too many arguments.", 1);
    }

    return 0;
}

int32_t
builtin_setenv(shell_t *shell)
{
    COMMAND_FOUND;
    int32_t in_env = 0, mode_builtin = 1;
    char **arg = parse_stdin(shell->get_line, shell);
    int32_t len_arg = len_array(arg);
    if (len_arg == 1) {
        print_array(shell->set_env->env_array, '\n');
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (error_case_no_str_is_alpha(shell, len_arg) == 1) {
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (len_arg != 1)
        already_in_env(shell, mode_builtin);
    if (len_arg > 3) {
        EXIT_W_ECHO_ERROR_("setenv: Too many arguments.", 1);
    }
    builtin_setenv_ext(shell, len_arg, in_env, mode_builtin);
    UPDATE_SUCCESS_STATUS;
    return 0;
}

int32_t
builtin_unsetenv(shell_t *shell)
{
    int32_t count = 0, in_env = 0, mode_builtin = 0;
    shell->mode = 0;
    COMMAND_FOUND;
    char **arg = parse_stdin(shell->get_line, shell);
    int32_t len_arg = len_array(arg);
    int32_t len_env = len_array(shell->set_env->env_array);
    if (error_case_no_str_is_alpha(shell, len_arg) == 3)
        return 0;
    count = already_in_env(shell, mode_builtin);
    if (len_env == count) {
        UPDATE_SUCCESS_STATUS; return 0;
    }
    if (len_arg == 1) {
        EXIT_W_ECHO_ERROR_("unsetenv: Too few arguments.", 1);
    }
    builtin_unsetenv_ext(shell, in_env, len_arg);
    UPDATE_SUCCESS_STATUS;
    return 0;
}

int32_t
builtin_env(shell_t *shell)
{
    COMMAND_FOUND;
    print_array(shell->set_env->env_array, '\n');
    UPDATE_SUCCESS_STATUS;
    return 0;
}
