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

int32_t
clear_term(shell_t *shell UNUSED_ARG)
{
    COMMAND_FOUND;

    _print("\033[2J\033[H");
    /* Use of rl_redisplay rather than rl_forced_update_display because,
    logically, the prompt is no longer necessary */
    rl_replace_line("", 0);
    rl_redisplay();
    return 0;
}

int32_t
clear_wrapper(int start UNUSED_ARG, int end UNUSED_ARG)
{
    /* Do not call builtin clear_term function */
    _print("\033[2J\033[H");
    /* Use rl_forced_update_display instead of rl_redisplay to keep the prompt when CTRL + L is pressed. */
    rl_forced_update_display();


    return 0;
}
