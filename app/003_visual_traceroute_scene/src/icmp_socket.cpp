/*
 *  Cairim App: Visual Traceroute Scene
 *  Copyright (C) 2020 Johan Norberg <lonezor@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>
 */

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
    memset(buffer, 0, sizeof(buffer));

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
