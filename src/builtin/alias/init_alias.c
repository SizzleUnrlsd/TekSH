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
init_alias(shell_t *shell)
{
    shell->call_alias = malloc_attribut(sizeof(call_alias_t), shell);
    shell->call_alias->info_alias =
    malloc_attribut(sizeof(info_alias_t), shell);
    shell->call_alias->alias =
    calloc_attribut(sizeof(alias_t *), SET_ALIAS, shell);
    shell->call_alias->info_alias->is_an_alias = false;
    shell->call_alias->info_alias->current_alloc = 0;
    shell->call_alias->info_alias->nb = 1;
    return;
}
