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

#include "shell.h"

#ifndef DEBUG
    sigjmp_buf env_stack;
    void catch_segv(int32_t sig)
    {
        pfflush_wrapper(STDERR_FILENO, "SEGFAULT[%d]\n", sig);
        siglongjmp(env_stack, 1);
    }
#endif

shell_conf_t globalConfig;

void shell_engine(shell_t *shell, char **env)
{
    char *new_line = NULL;
    call_alias_t *call_alias = NULL;
    shell_requirement(shell, env, &call_alias);

    while (true) {
        if (prompt_shell(shell) == 42) {
            ENDING_PROCESS_("exit", 0);
        }
        if (format_getline(shell, &shell->get_line)) {
            continue;
        }
        new_line = format_alias_getline(shell, shell->get_line);

        if (shell->call_alias->info_alias->is_an_alias != false) {
            shell->get_line = strdup(new_line);
        }

        #ifndef DEBUG
            if (sigsetjmp(env_stack, 1) == 0) {
                ast_final(shell->get_line, shell);
            } else {
                FILE* file = fopen("mini_dump/error_promt_cmd", "a");
                char log[256];
                sprintf(log, "%s/%s", shell->get_line, ARCH);
                fprintf(file, "%s\n", log);
                fclose(file);
            }
        #else
            ast_final(shell->get_line, shell);
        #endif
    }
}

void
shell_theme()
{
    // work in progress
}

int main(int32_t ac, char **av, char **env)
{
    shell_t *shell = DEFAULT(shell);
    pid_t pid;
    parse_arg(ac, av);

#ifndef DEBUG
    signal(SIGSEGV, catch_segv);
#endif

    shell = init_shell();
    shell_theme();

    pid = fork();
    if (pid == 0) {
        check_version(shell);
    }
    if (pid != 0) {
        if (waitpid(pid, NULL, 0) == -1) {
            return !!_FORK_ERROR;
        }
        shell_engine(shell, env);
    }
    return 0;
}
