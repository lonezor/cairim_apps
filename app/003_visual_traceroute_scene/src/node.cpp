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

#include "node.hpp"

namespace vtr {

node::node(std::string ip_addr, std::string fqdn, uint64_t rtt)
    : ip_addr_(ip_addr)
    , fqdn_(fqdn)
    , rtt_(rtt)
{

}

std::string node::get_ip_addr()
{
    return ip_addr_;
}

std::string node::get_fqdn()
{
    return fqdn_;
}

uint64_t node::get_access_counter()
{
    return access_counter_;
}

uint64_t node::get_rtt()
{
    return rtt_;
}

void node::increment_access_counter()
{
    access_counter_++;
}

} // namespace vtr