#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/shell.h"

#define ANSI_COLOR_RED     "\x1b[31m"

int execution(void)
{
    // printf("\033[0;31m");
    printf(ANSI_COLOR_RED);
    return 0;
}

plugin_t *
init(void)
{
    plugin_t *plugin = malloc(sizeof(plugin_t));
    if (!plugin) {
        exit(EXIT_FAILURE);
    }

    plugin->execute = &execution;
    plugin->command = strdup("red_term");

    return plugin;
}
