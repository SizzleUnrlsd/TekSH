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

#ifndef BASIC_FUNCTION_H_
    #define BASIC_FUNCTION_H_
    #include "glibc.h"
    #include "struct.h"
    #include "alias.h"

        /* G_LIBC_FUNCTION_H_ */

    char *chr_to_str(char c);
    char *_getch(int32_t a);
    int32_t _put_nbr(long nb);
    int32_t char_isalpha(char c);
    int32_t char_isdigit(char c);
    int32_t char_isspace(char c);
    int32_t char_isalnum(char c);
    int32_t _strlen(char const *str);
    int32_t stat_copy(char const *str);
    int32_t _get_nbr(char const *str);
    char _putchar(char c, int32_t fd);
    int32_t _get_key(int32_t a, char *str);
    int32_t _putstr(char const *str, int32_t fd);
    char *_strcpy(char *dest, char const *src);
    char *_strcat(char *dest, char const *src);
    size_t _strnlen(const char *s, size_t maxlen);
    int32_t _strcmp(char const *s1, char const *s2);
    char *_strndup(const char *s, size_t n);
    char *_strdup(char const *src, shell_t *shell);
    char *_strncpy(char *dest, char const *src, uint32_t n);
    int32_t _strncmp(char const *s1, char const *s2, uint32_t n);
    char **_str_to_word_array_custom(shell_t *shell, char *str, char c);
    char **re_alloc(shell_t *shell, char **src,
            int32_t len_src, int32_t len_dest);
    char **_str_to_word_array_custom_double(shell_t *shell, char *str,
                                                        char c, char x);

        /* INIT_SHELL */

    void shell_requirement(shell_t *shell, char **env, call_alias_t **call_alias);
    int32_t check_perm_dollar_engine(char *arg, char *value, shell_t *shell);
    int32_t dollar_engine(char **arg, int32_t i, shell_t *shell);

        /* IO_STREAM */

    void pfflush(const char *format, va_list ap);
    void vpfflush(const char *format, va_list ap);
    void pfflush_wrapper(int32_t fd, const char *format, ...);

        /* FORMAT_COMMAND_LINE_H_ */

    void clean_str(char *str);
    shell_t *init_shell(void);
    void format_arg(char **arg);
    int32_t len_array(char **array);
    char *remove_back_n(char *src);
    void print_array(char **array, char c);
    void retrieve_env(shell_t *shell, char **env);
    void print_str(char const *str, char c, bool print, int32_t fd);
    char *del_one_char(shell_t *shell, char **src, char *dest);
    char *concat_char_str(char concat, char *str, int32_t futur, int32_t a);

        /* BULTIN_H_ */

    int32_t _echo(shell_t *shell);
    int32_t builtin_cd(shell_t *shell);
    int32_t builtin_env(shell_t *shell);
    int32_t builtin_exit(shell_t *shell);
    int32_t builtin_setenv(shell_t *shell);
    int32_t is_same_char(char const *path);
    int32_t builtin_unsetenv(shell_t *shell);
    char *find_home(shell_t *shell, char *home);
    void sort_in_int_array(int *a, int32_t len);
    int32_t is_builtin(shell_t *shell, char *cmd);
    int32_t build_cd_bar(shell_t *shell, char **arg);
    int32_t already_in_env(shell_t *shell, int32_t mode);
    int32_t pwd_already_ini_env(shell_t *shell, char *str);
    int32_t exit_error(shell_t *shell, char **arg, int32_t len_arg);
    int32_t builtin(shell_t *shell, char **path, uint32_t *rd_builtin);
    int32_t error_case_no_str_is_alpha(shell_t *shell, int32_t len_arg);
    void add_line_to_array(shell_t *shell, int32_t len_arg, int32_t in_env);
    int32_t check_perm_dir(shell_t *shell, char *path, uint32_t *invalid_cd);
    void builtin_unsetenv_ext(shell_t *shell, int32_t in_env, int32_t len_arg);
    int32_t build_cd_foobar(shell_t *shell, char **arg,
                int32_t len_arg, uint32_t *invalid_cd);
    int32_t build_cd_foo(shell_t *shell, char *home,
                        char **arg, int32_t len_arg);
    void builtin_setenv_ext(shell_t *shell, int len_arg,
                        int32_t in_env, int mode_builtin);
    int32_t function_set_param_env(int32_t i, char **env,
                        char **first_step,  shell_t *shell);

    char *remove_space_before_string(const char *str);
    void remove_newline(char *str);

        /* PROMPT_ */

    int32_t is_bin(char const *path);
    int32_t is_dir(char const *path);
    int32_t prompt_shell(shell_t *shell);
    void reset_var_shell(shell_t *shell);
    char *cut_into_command(char *command);
    void parse_command(char *cmd, char **args);
    void parent_exit(shell_t *shell, int32_t wstatus);
    char **parse_stdin(char *command, shell_t *shell);
    char **cut_path_env(shell_t *shell, char **array);
    bool format_getline(shell_t *shell, char **command);
    void execute_command(char **arg, shell_t *shell);
    int32_t access_file(shell_t *shell, char **path);
    int32_t open_directory(shell_t *shell, char **path, char **arg);
    int32_t prompt_function(shell_t *shell, set_env_t *env_set, char **arg);

        /* PROMPT_TOOLS_ */

    void del_space_end_str(char *command);
    void delete_semicolon_end(char *command);
    void remove_backslash_n(char *command);
    void delete_spaces_tabulations(char *command);
    void replace_multiple_spaces_tabulations(char *command);
    void first_command_is_misplaced(char *command, unsigned char  *c);
    void last_character_not_space_or_tabulation(char *command,
                                            unsigned char *c);
    int32_t find_shell_inconsistency(char *command, shell_t *shell);
    bool contains_one_multiple(char *command, char *special_chars);
    bool contains_special_combinations(char *command, char *special_chars);

        /* ALIAS */

    void init_alias(shell_t *shell);
    int alias_engine(shell_t *shell);
    void set_alias(call_alias_t *call_alias);
    char *format_alias_getline(shell_t *shell, char *cmd);
    int len_needed(char **arr_line, int index);
    void print_all_alias(call_alias_t *call_alias);
    void if_alias_find(call_alias_t *call_alias, shell_t *shell, int cpt,
                                                            char **arr_line);
    char * give_all_options(char **arr_line, int index, shell_t *shell);

        /* HISTORY */

    int builtin_history(shell_t *shell);
    int builtin_exclamation(shell_t *shell);
    int create_history(char *str);
    void flag_help(void);
    void flag_clear(char *str);
    int write_in_file(shell_t *shell);
    void init_history(shell_t *shell);

        /* LOADER */

    int32_t loader(shell_t *shell, char **command);

        /* VERSION */

    char *getgit_branch();
    int32_t check_version(void);
    void handleVersion(void);

        /* PARSE_ARG */

    void parse_arg(int32_t ac, char **av);

#endif /* !BASIC_FUNCTION_H_ */
