#pragma once

#include <string>
#include <stdint.h>

#include "socket.hpp"

namespace vtr {

class tcp_socket : public socket
{
    public:
        tcp_socket(int af, std::string dst_ip, int port);

        void set_syn_retries(int retries);

        // connect is deliberately separated from the constructor
        // since the primary use case is to fail connect() while
        // increasing the hop limit
        bool connect(uint64_t* time);

    private:
        std::string dst_ip_;
        int port_;
        int hop_limit_;
};

} // namespace vtr