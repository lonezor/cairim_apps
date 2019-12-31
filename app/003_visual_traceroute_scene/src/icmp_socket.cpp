#include <arpa/inet.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "icmp_socket.hpp"
#include "dns_resolver.hpp"

namespace vtr {

icmp_socket::icmp_socket(int af)
  : socket(af)
{
  fd_ = ::socket(af_, SOCK_RAW, IPPROTO_ICMP);
}

icmp_socket::~icmp_socket()
{

}

bool icmp_socket::recv_hop_limit_exceeded(std::string& ip_address, std::string& fqdn)
{
    uint8_t buffer[128];

    auto res = recv(fd_, buffer, sizeof(buffer), 0);

    if (buffer[20] == 0x0b && buffer[21] == 0x00) {
      uint32_t src_address;
      memcpy(&src_address, &buffer[12], 4);
      struct in_addr addr;
      addr.s_addr = src_address;

      char* ip = inet_ntoa(addr);
      if (ip) {
        ip_address = std::string(ip);
      }

      fqdn = dns_resolver::ip_to_fqdn((uint8_t*)&src_address, sizeof(src_address));
      
      return true;
    }

    return false;
}

} // namespace vtr
