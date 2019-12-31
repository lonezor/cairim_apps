#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#include "common.hpp"

namespace vtr {

class socket
{
    public:
        socket(int af);
        ~socket();

        int get_fd();
        int get_af();

        void set_hop_limit(int limit);
        void set_recv_timeout(int timeout_ms);

        bool connect(std::string dst_ip, int port);


        void close();

    protected:
        int fd_{-1};
        int af_;
};

} // namespace vtr