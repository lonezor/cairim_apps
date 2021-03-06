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

#include "server_path.hpp"
#include "dns_resolver.hpp"
#include "time_utils.hpp"
#include "tcp_socket.hpp"
#include "icmp_socket.hpp"
#include "node.hpp"

namespace vtr {

server_path::server_path(std::string fqdn)
 : fqdn_(fqdn)
{
    server_ip_ = dns_resolver::fqdn_to_ip(fqdn_, af_);
}

void server_path::discover(int max_hop_limit)
{
    int ttl = 0;

    auto icmp = icmp_socket(af_);
    icmp.set_recv_timeout(1000);

    while (ttl++ < max_hop_limit) {
      auto tcp = tcp_socket(AF_INET, server_ip_, 443);
      tcp.set_syn_retries(1);

      tcp.set_hop_limit(ttl);

      uint64_t rtt = 0;
      bool conn_success = tcp.connect(&rtt);
      if (conn_success) {
        break;
      }

      std::string hle_ip;
      std::string hle_fqdn;
      icmp.recv_hop_limit_exceeded(hle_ip, hle_fqdn);

      auto n = node(hle_ip, hle_fqdn, rtt);
      nodes_.emplace_back(n);
    }
}

std::vector<node> server_path::get_nodes()
{
  return nodes_;
}

std::string server_path::get_fqdn()
{
  return fqdn_;
}

void server_path::print()
{
  int i = 0;
  for(auto && n : nodes_) {
    std::cout << "{"
    << fqdn_ 
    << " / " 
    << server_ip_ 
    << "}" 
    << " Hop limit " 
    << i++ + 1 
    << ", RTT " 
    << n.get_rtt() 
    << " --> { " 
    << n.get_fqdn()
    << " / "
    << n.get_ip_addr()
    << "}"
    << std::endl;
  }
}

} // namespace vtr
