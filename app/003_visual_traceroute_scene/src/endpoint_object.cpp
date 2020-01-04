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

#include <stdlib.h>

#include "endpoint_object.hpp"

namespace vtr {
    
endpoint_object::endpoint_object(double x, double y, double width, double height,
    std::shared_ptr<rendering_context> rc, std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{

}

void endpoint_object::set_description(std::string desc)
{
    desc_ = desc;
}

void endpoint_object::draw(frame_context& fc)
{
    if (!desc_.empty()) {
        double middle_pos = static_cast<double>(desc_.size()) / 2;
        size_t text_pos_x = x_ - (middle_pos * 7);
        size_t text_pos_y = y_ + (height_ / 2) + 5;

        rc_->set_source_rgba(1, 1, 1, 1);
        rc_->font_size(12);
        rc_->move_to(text_pos_x, text_pos_y);
        rc_->show_text(desc_);
    }

    draw_svg_surface(x_, y_, 1.0, 0.0);
}

} // namespace vtr
