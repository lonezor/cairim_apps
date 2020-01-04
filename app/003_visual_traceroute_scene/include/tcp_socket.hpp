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

#include <string>
#include <stdint.h>

#include "socket.hpp"

namespace vtr {

class tcp_socket : public socket
{
    public:
        tcp_socket(int af, std::string dst_ip, int port);

        void set_syn_retries(int retries);

        // connect is deliberately separated from the constructor
        // since the primary use case is to fail connect() while
        // increasing the hop limit
        bool connect(uint64_t* time);

    private:
        std::string dst_ip_;
        int port_;
        int hop_limit_;
};

} // namespace vtr