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

#include "star.hpp"    
#include <stdlib.h>
    
star::star(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{
    // Brightness animation based on size
    step_ = 0.0020 * (width);
}

void star::draw(frame_context& fc)
{
    // Let alpha continuously go down and up
    alpha_ -= step_;
    if (alpha_ < 0.5) {
        alpha_ = 0.5;
        step_ *= -1;
    } else if (alpha_ > 1.0) {
        alpha_ = 1.0;
        step_ *= -1;
    }

    draw_svg_surface(x_, y_, alpha_, 0.0);
}

