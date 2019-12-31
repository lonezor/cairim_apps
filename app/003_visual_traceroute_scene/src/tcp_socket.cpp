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

#include "tcp_socket.hpp"
#include "time_utils.hpp"

namespace vtr {

tcp_socket::tcp_socket(int af, std::string dst_ip, int port)
 : socket(af)
 , dst_ip_(dst_ip)
 , port_(port)
{
  fd_ = ::socket(af_, SOCK_STREAM, 0);
}

void tcp_socket::set_syn_retries(int retries)
{
  setsockopt(fd_, IPPROTO_TCP, TCP_SYNCNT, &retries, sizeof(retries));
}

bool tcp_socket::connect(uint64_t* time)
{
  auto t1 = time_utils::get_ts();
  auto res = socket::connect(dst_ip_, port_);
  auto t2 = time_utils::get_ts();

  *time = t2 - t1;  
  return res == 0;
}

} // namespace vtr