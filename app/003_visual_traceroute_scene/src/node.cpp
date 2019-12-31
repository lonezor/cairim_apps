
#include "node.hpp"

namespace vtr {

node::node(std::string ip_addr, std::string fqdn, uint64_t rtt)
    : ip_addr_(ip_addr)
    , fqdn_(fqdn)
    , rtt_(rtt)
{

}

std::string node::get_ip_addr()
{
    return ip_addr_;
}

std::string node::get_fqdn()
{
    return fqdn_;
}

uint64_t node::get_access_counter()
{
    return access_counter_;
}

uint64_t node::get_rtt()
{
    return rtt_;
}

} // namespace vtr