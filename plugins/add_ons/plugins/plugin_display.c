#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/shell.h"

int
execution_disp(int ac, char **av)
{
    printf("like a main function argc -> {%d}\n", ac);
    for (int i = 0; av[i]; i++)
        printf("argv[%d] -> {%s}\n", i, av[i]);
    printf("Example of running the 'Hello' command\n");
    return 0;
}

plugin_t *
init(void)
{
    plugin_t *plugin = (plugin_t*)malloc(sizeof(plugin_t *));
    if (!plugin) {
        exit(EXIT_FAILURE);
    }
    plugin->execute = execution_disp;
    plugin->command = strdup("Hello");
    return plugin;
}
