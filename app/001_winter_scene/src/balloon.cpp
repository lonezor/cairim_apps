/*
 *  Cairim App: Winter Scene
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

#include "balloon.hpp"    
#include <stdlib.h>
    
balloon::balloon(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{

}

void balloon::draw(frame_context& fc)
{
    // Too low: force upwards
   if (y_ > 370) {
       thrust_ += 0.004;
   }

   // Too high: force downwards
   else if (y_ < 185) {
       thrust_ -= 0.004;
   }

    if (thrust_ < 0) {
        thrust_ = 0;
    } else if (thrust_ > 1) {
        thrust_ = 1;
    }

    x_ += 0.3 + (thrust_ / 2);
    y_ += 0.5 - thrust_;
    
    draw_svg_surface(x_, y_, 0.95, 0.0);
}

