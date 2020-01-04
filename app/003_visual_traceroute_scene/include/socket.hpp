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

#pragma once

#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

#include "common.hpp"

namespace vtr {

class socket
{
    public:
        socket(int af);
        ~socket();

        int get_fd();
        int get_af();

        void set_hop_limit(int limit);
        void set_recv_timeout(int timeout_ms);

        bool connect(std::string dst_ip, int port);

        void close();

    protected:
        int fd_{-1};
        int af_;
};

} // namespace vtr