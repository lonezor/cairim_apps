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

#include "spiral.hpp"    
#include <stdlib.h>
#include <cmath>
    
spiral::spiral(double x, double y, double width, double height, double velocity, double max_radius, std::shared_ptr<rendering_context> rc)
    : object(x,y,width,height, rc, "")
    , velocity_(velocity)
    , max_radius_(max_radius)
{
    origo_x_ = x;
    origo_y_ = y;
}

void spiral::draw(frame_context& fc)
{
    fc.scene_width = width_;
    fc.scene_height = height_;

    radius_ += velocity_;
    bool complete = false;
    if (radius_ > max_radius_) {
        radius_ = max_radius_;
        complete = true;
    }

    // Theta, expressed as range 0.0 - 1.0
    theta_ += 0.01;
    if (theta_ > 1) {
        theta_ = 0;
    }

    x_ = origo_x_ + radius_ * cos(2 * m_pi * theta_);
    y_ = origo_y_ + radius_ * sin(2 * m_pi * theta_);

    if (!complete) {
        points_.emplace_back(new_point(x_, y_));
    }
    
    rc_->move_to(origo_x_,origo_y_);
    rc_->line_width(2);
    rc_->set_source_rgb(1,1,1);
    for(auto&& p : points_)
    {
        rc_->line_to(p.x, p.y);
        rc_->move_to(p.x, p.y);
    }
    
    rc_->stroke();
}

point_entry spiral::new_point(double x, double y)
{
    point_entry p = {x, y};
    return p;
}
