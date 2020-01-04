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

#include "time_utils.hpp"

#include <time.h>

namespace vtr {
namespace time_utils {

uint64_t get_ts() {
  uint64_t ts;
  struct timespec now;

  if (clock_gettime(CLOCK_MONOTONIC, &now)) {
    return 0;
  }

  ts = (uint64_t)now.tv_sec * 1000000LLU;
  ts += (uint64_t)now.tv_nsec / 1000LLU;

  return ts;
}

} // namespace time_utils
} // namespace vtr

