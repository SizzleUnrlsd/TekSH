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

#ifndef DEBUG
sigjmp_buf env_stack;

_VOID void catch_segv(int32_t sig)
{
    pfflush_wrapper(STDERR_FILENO, "SEGFAULT[%d]\n", sig);
    siglongjmp(env_stack, 1);
}
#endif

shell_conf_t globalConfig;

void shell_engine(shell_t *shell, char **env)
{
    char *restrict new_line = DEFAULT(new_line);
    call_alias_t *call_alias = DEFAULT(call_alias);
    shell_requirement(shell, env, &call_alias);

    while (true) {
        if (prompt_shell(shell) == 42) {
            ENDING_PROCESS_("exit", 0);
        }
        if (char_stream_formatting(shell, &shell->line)) {
            continue;
        }
        new_line = format_alias_getline(shell, shell->line);

        if (shell->call_alias->info_alias->is_an_alias != false) {
            shell->line = _strdup(new_line);
        }
#ifndef DEBUG
        if (sigsetjmp(env_stack, 1) == 0) {
            ast_final(shell->line, shell);
            rl_cleanup_after_signal();
            rl_free_line_state();
            garbage_routine();
        } else {
            saving_error_file(shell);
        }
#else
        ast_final(shell->line, shell);
        rl_cleanup_after_signal();
        rl_free_line_state();
        garbage_routine();
#endif
    }
}

void
shell_theme()
{
    // work in progress
}

int main(int32_t ac UNUSED_ARG, char **av, char **env UNUSED_ARG)
{
    shell_t *shell = DEFAULT(shell);

    garbage_constructor();
    parse_arg(ac, av);

#ifndef DEBUG
    signal(SIGSEGV, catch_segv);
#endif

    shell = init_shell();
    shell_theme();
    shell_engine(shell, env);
    return 0;
}
