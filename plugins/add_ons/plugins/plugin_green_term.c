#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/shell.h"

int execution(void)
{
    printf("\033[0;32m");
    return 0;
}

plugin_t* init(void)
{
    plugin_t* plugin = malloc(sizeof(plugin_t));
    if (plugin == NULL) {
        exit(EXIT_FAILURE);
    }

    plugin->execute = &execution;
    plugin->command = strdup("green term");

    return plugin;
}

