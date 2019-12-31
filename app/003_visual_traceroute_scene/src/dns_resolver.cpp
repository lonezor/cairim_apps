#include <time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ares.h>
#include <sys/time.h>
#include <string.h>


#include "dns_resolver.hpp"

namespace vtr {
namespace dns_resolver {

static void ares_ip_cb(void* arg, int status, int timeouts, struct hostent* host)
{
    if(status == ARES_SUCCESS) {
        char** result = (char**)arg;
        char buff[INET6_ADDRSTRLEN];

        int prot = host->h_addrtype;
        for (int i = 0; host->h_addr_list[i]; ++i) {
            if (inet_ntop(prot, host->h_addr_list[i], buff, INET6_ADDRSTRLEN)) {
                *result = strdup(buff);
            }
            break;
        }
    }
}

static void ares_fqdn_cb(void* arg, int status, int timeouts, struct hostent* host)
{
    if(status == ARES_SUCCESS) {
        char** result = (char**)arg;
        char buff[INET6_ADDRSTRLEN];

        if (host->h_name != nullptr) {
            *result = strdup(host->h_name);
        }
    }
}

static void ares_loop(ares_channel channel)
{
    int nfds, count;
    fd_set readers, writers;
    struct timeval tv;
    struct timeval* tvp;
    while (1) {
        FD_ZERO(&readers);
        FD_ZERO(&writers);
        nfds = ares_fds(channel, &readers, &writers);
        if (nfds == 0) {
          break;
        }
        tvp = ares_timeout(channel, NULL, &tv);
        count = select(nfds, &readers, &writers, NULL, tvp);
        ares_process(channel, &readers, &writers);
     }
}

std::string fqdn_to_ip(std::string fqdn, int family)
{
    ares_channel channel;
    int res = ares_init(&channel);
    
    if (res != ARES_SUCCESS) {
        return "";
    }

    char* addr = NULL;
    ares_gethostbyname(channel, fqdn.c_str(), family, ares_ip_cb, &addr);
    ares_loop(channel);

    
    std::string address;
    if (addr) {
        address = std::string(addr);
        free(addr);
    }

    ares_destroy(channel);

    return address;
}

std::string ip_to_fqdn(uint8_t* addr, int len)
{
    ares_channel channel;
    int res = ares_init(&channel);
    
    if (res != ARES_SUCCESS) {
        return "";
    }
    
    char* name = NULL;
    ares_gethostbyaddr(channel, addr, len, AF_INET, ares_fqdn_cb, &name);
    ares_loop(channel);

    std::string fqdn;
    if (name) {
        fqdn = std::string(name);
        free(name);
    }

    ares_destroy(channel);

    return fqdn;
}

} // namespace dns_resolver
} // namespace vtr
