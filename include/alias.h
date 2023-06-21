/*
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

#ifndef ALIAS_H_
    #define ALIAS_H_

    #include "glibc.h"

    #define SET_ALIAS 20
    #define ACCEPTANCE 5

    typedef struct alias_s {
        char *cmd_alias;
        char *cmd_is_replace;
    }alias_t;

    typedef struct info_alias_s {
        size_t nb;
        int is_an_alias;
        int current_alloc;
    }info_alias_t;

    typedef struct call_alias_s {
        alias_t **alias;
        info_alias_t *info_alias;
    }call_alias_t;

#endif /* !ALIAS_H_ */
