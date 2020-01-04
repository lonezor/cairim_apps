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

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#include "socket.hpp"

namespace vtr {

socket::socket(int af)
 : af_(af)
{
  // fd_ created by derived class
}

socket::~socket()
{
  close();
}

void socket::set_hop_limit(int limit)
{
  auto res = setsockopt(fd_, IPPROTO_IP, IP_TTL, &limit, sizeof(limit));
}

void socket::set_recv_timeout(int timeout_ms)
{
  // Set receive timeout
  struct timeval timeout;
  timeout.tv_sec = (long)1;
  timeout.tv_usec = 0;

  int res = setsockopt(fd_, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                       sizeof(timeout));
  if (res < 0) {
    perror("sockopt");
  }

}

bool socket::connect(std::string dst_ip, int port)
{
  struct sockaddr_in addr;
  memset(&addr, 0, sizeof(addr));
  
  addr.sin_family = af_;
  addr.sin_addr.s_addr = inet_addr(dst_ip.c_str()); 
  addr.sin_port = htons(port);

  assert(af_ == AF_INET);

  auto res = ::connect(fd_, (struct sockaddr*)&addr, sizeof(addr));

  return res != 0;
}



int socket::get_fd()
{
  return fd_;
}

int socket::get_af()
{
  return af_;
}

void socket::close()
{
  if (fd_ != -1) {
    ::close(fd_);
    fd_ = -1;
  }
}

} // namespace vtr