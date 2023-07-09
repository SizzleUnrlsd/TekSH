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

uint32_t job_control;
uint32_t supposed_job_control;

void
reset_var_shell(shell_t *shell)
{
    shell->command_not_found = 0;
    shell->binary = 0;
    shell->built_shell_type_env = 0;
    shell->built_exit = 0;
    shell->get_line = NULL;
    shell->len_arg = 0;
    job_control = 0;

    return;
}
