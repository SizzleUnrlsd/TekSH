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

void
saving_error_file(shell_t *shell)
{
    const char *restrict path = "mini_dump/error_promt_cmd";
    const char *restrict mode = "a";
    FILE* file = fopen(path, mode);
    char log[256] = {0};

    sprintf(log, "%s/%s", shell->line, ARCH);
    fprintf(file, "%s\n", log);
    fclose(file);
}
