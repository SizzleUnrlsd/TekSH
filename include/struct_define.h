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

#ifndef STRUCT_DEFINE_H_
    #define STRUCT_DEFINE_H_
    #define BUILT_IN_NB 0
    #define RD_TTY shell->print
    #define BINARY  shell->binary
    #define LEN_ARRAY_STRUCT 100000
    #define ENV_PATH shell->set_env->path_env
    #define BUILT_INT_EXIT shell->built_exit
    #define SHELL_ENV shell->built_shell_type_env
    #define ENV_SET_ARRAY shell->set_env->env_array
    #define FULL_ARRAY_ENV shell->set_env->env_array
    #define PATH_HISTORY_FILE "teksh_history"

    #define ERROR_SET_UNSET_FIRST_DOLLAR "unsetenv: \
Variable name must begin with a letter."
    #define ERROR_SET_UNSET_LAST_DOLLAR  "unsetenv: \
Variable name must contain alphanumeric characters."
    #define ERROR_SETENV_FIRST_DOLLAR "setenv: \
Variable name must begin with a letter."
    #define ERROR_SETENV_LAST_DOLLAR  "setenv: \
Variable name must contain alphanumeric characters."
    #define ERROR_SET_UNSET_DOLLAR ": Undefined variable."

#endif /* !STRUCT_DEFINE_H_ */
