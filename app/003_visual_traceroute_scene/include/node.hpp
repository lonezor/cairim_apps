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

#include "common.hpp"

namespace vtr {

class node
{
    public:
        node(std::string ip_addr, std::string fqdn, uint64_t rtt);

        std::string get_ip_addr();
        std::string get_fqdn();
        uint64_t get_access_counter();
        uint64_t get_rtt();

        void increment_access_counter();

    private:
        std::string ip_addr_;
        std::string fqdn_;
        uint64_t access_counter_{0};
        uint64_t rtt_; // unit: microseconds
};

} // namespace vtr

