#pragma once

#include "common.hpp"

namespace vtr {

class node
{
    public:
        node(std::string ip_addr, std::string fqdn, uint64_t rtt);

        std::string get_ip_addr();
        std::string get_fqdn();
        uint64_t get_access_counter();
        uint64_t get_rtt();

        void increment_access_counter();

    private:
        std::string ip_addr_;
        std::string fqdn_;
        uint64_t access_counter_{0};
        uint64_t rtt_; // unit: microseconds
};

} // namespace vtr

