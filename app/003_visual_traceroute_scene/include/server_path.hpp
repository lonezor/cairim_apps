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

#include <vector>
#include <arpa/inet.h>

#include "node.hpp"

namespace vtr {

constexpr int hop_limit_max = 255;

class server_path
{
    public:
        server_path(std::string fqdn);

        void discover(int max_hop_limit);
        void print();

        std::vector<node> get_nodes();
        std::string get_fqdn();

    private:
        std::vector<node> nodes_;
        std::string server_ip_; // target IP
        std::string fqdn_; // target FQDN
        int af_{AF_INET};
};

} // namespace vtr