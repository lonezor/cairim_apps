#pragma once


#include <vector>
#include <arpa/inet.h>

#include "node.hpp"

namespace vtr {

constexpr int hop_limit_max = 255;

class server_path
{
    public:
        server_path(std::string fqdn);

        void discover(int max_hop_limit);
        void print();

        std::vector<node> get_nodes();
        std::string get_fqdn();

    private:
        std::vector<node> nodes_;
        std::string server_ip_; // target IP
        std::string fqdn_; // target FQDN
        int af_{AF_INET};
};

} // namespace vtr