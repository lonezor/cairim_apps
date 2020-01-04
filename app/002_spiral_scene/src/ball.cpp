/*
 *  Cairim App: Spiral Scene
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

#include "ball.hpp"    
#include <stdlib.h>
    
ball::ball(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{
}

void ball::draw(frame_context& fc)
{
    x_ += velocity_x_;
    y_ += velocity_y_;
    if (x_ > fc.scene_width || x_ < 0) {
        velocity_x_ *= -1;
    }
    if (y_ > fc.scene_height || y_ < 0) {
        velocity_y_ *= -1;
    }

    draw_svg_surface(x_, y_, 1.0, 0.0);
}

