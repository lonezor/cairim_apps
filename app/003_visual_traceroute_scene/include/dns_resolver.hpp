#pragma once

#include <string>
#include <stdint.h>

namespace vtr {
namespace dns_resolver {

std::string fqdn_to_ip(std::string fqdn, int family);
std::string ip_to_fqdn(uint8_t* addr, int len);

} // namespace dns_resolver
} // namespace vtr


