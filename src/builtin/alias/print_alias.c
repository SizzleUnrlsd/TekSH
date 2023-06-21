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
print_all_alias(call_alias_t *call_alias)
{
    size_t cpt = 0;
    if (call_alias->alias != NULL) {
        while (cpt != call_alias->info_alias->nb) {
            _print("alias ");
            _printf("%s ", call_alias->alias[cpt]->cmd_alias);
            _printf("%s\n", call_alias->alias[cpt]->cmd_is_replace);
            cpt++;
        }
    }
}
