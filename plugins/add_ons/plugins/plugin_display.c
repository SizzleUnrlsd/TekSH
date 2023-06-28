#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/shell.h"

int
execution_disp(void)
{
    printf("execution of the 'Hello' command.\n");
    return 0;
}

plugin_t *
init(void)
{
    plugin_t *plugin = malloc(sizeof(plugin_t));
    if (!plugin) {
        exit(EXIT_FAILURE);
    }
    plugin->execute = execution_disp;
    plugin->command = strdup("Hello");
    return plugin;
}
