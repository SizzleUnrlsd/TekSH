#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/shell.h"

int
execution(void)
{
    printf("Command execution\n");
    return 0;
}

plugin_t *
init(void)
{
    plugin_t *plugin = malloc(sizeof(plugin));
    if (plugin == NULL) {
        exit(EXIT_FAILURE);
    }
    plugin->execute = &execution;
    plugin->command = strdup("nm");

    return plugin;
}
