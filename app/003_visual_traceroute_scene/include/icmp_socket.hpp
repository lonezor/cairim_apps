#pragma once

#include "socket.hpp"

#include <string>

namespace vtr {

class icmp_socket : public socket
{
    public:
        icmp_socket(int af);
        ~icmp_socket();

        bool recv_hop_limit_exceeded(std::string& ip_address, std::string& fqdn);
};

} // namespace vtr