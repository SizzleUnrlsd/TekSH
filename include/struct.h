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

#ifndef STRUCT_H_
    #define STRUCT_H_
    #include "garbage_collector.h"
    #include "bultin_global_env.h"
    #include "history.h"
    #include "alias.h"

    typedef struct shell_s {
        history_t *history;
        set_env_t *set_env;
        garbage_collector_t **garbage;
        call_alias_t *call_alias;
        char **local_env;
        char **cmd;
        char *name;
        char *param;
        char *value;
        char *cd_old_path;
        char *line;
        char *cd_new_path;
        char *shell_color_code;
        int32_t *several_arg_builtin;
        int32_t binary;
        int32_t command_not_found;
        int32_t built_shell_type_env;
        int32_t built_exit;
        int32_t built_nothing;
        int32_t len_arg;
        int32_t mode;
        int32_t status;
        uint32_t io;
        bool print;
        char padded[3];
    }shell_t;

    typedef struct shell_conf_s {
        char *version;
        char *theme;
    } shell_conf_t;

    extern shell_conf_t globalConfig;

    typedef struct flag_handler_s {
        const char* flag;
        void (*handler)();
    } flag_handler_t;

#endif /* !STRUCT_H_ */
