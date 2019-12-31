
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