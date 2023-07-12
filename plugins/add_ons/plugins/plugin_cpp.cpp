extern "C" {
#include "../../../include/shell.h"
}

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cstdint>
#include <arpa/inet.h>
#include <netdb.h>
#include <memory>

struct addrinfo_deleter
{
    void operator()(addrinfo* ptr) const
    {
        freeaddrinfo(ptr);
    }
};

using addrinfo_ptr = std::unique_ptr<addrinfo, addrinfo_deleter>;

int get_ip(char *name_addr)
{
    const char *hostname = name_addr;
    addrinfo hints;
    addrinfo *result_raw = nullptr;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_DGRAM;

    int status = getaddrinfo(hostname, NULL, &hints, &result_raw);
    if (status) {
        std::cerr << "getaddrinfo: " << gai_strerror(status) << '\n';
        return 1;
    }

    addrinfo_ptr result(result_raw);

    for (addrinfo *p = result.get(); p != nullptr; p = p->ai_next) {
        char addr_str[INET6_ADDRSTRLEN];

        std::cout << "type: " << p->ai_socktype << '\n';
        std::cout << "family: " << p->ai_protocol << '\n';

        void* addr;
        if (p->ai_family == AF_INET) {
            addr = &((sockaddr_in *)p->ai_addr)->sin_addr;
        } else {
            addr = &((sockaddr_in6 *)p->ai_addr)->sin6_addr;
        }

        inet_ntop(p->ai_family, addr, addr_str, INET6_ADDRSTRLEN);
        std::cout << "address: " << addr_str << '\n';
    }
    return 0;
}

extern "C" {

int execution_disp(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <hostname>\n";
        return 1;
    }
    get_ip(av[1]);
    return 0;
}

plugin_t * init()
{
    plugin_t *plugin = new plugin_t;
    if (!plugin) {
        std::exit(EXIT_FAILURE);
    }
    plugin->execute = execution_disp;
    plugin->command = strdup("get_ip");
    return plugin;
}

} // extern "C"
