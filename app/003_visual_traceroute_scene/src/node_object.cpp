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

#include "node_object.hpp"
#include <stdlib.h>

namespace vtr {
    
node_object::node_object(double x, double y, double width, double height, node& node,
    std::shared_ptr<rendering_context> rc, std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
    , node_(node)
{

}

void node_object::refresh_text_visibility()
{
    alpha_ = 1.0;
}

void node_object::draw(frame_context& fc)
{
    // Rectangle background
    rc_->set_source_rgb(0.2, 0.2, 0.2);
    rc_->rectangle(x_, y_, width_, height_);
    rc_->fill();

    // Access counter (number of IP packets)
    std::ostringstream access_counter;
    access_counter << node_.get_access_counter();
    rc_->set_source_rgb(1, 1, 1);
    rc_->font_size(16);
    rc_->move_to(x_ + (width_ / 2) - 4 , y_ + (height_ / 2) + 6);
    rc_->show_text(access_counter.str());

    // IP address    
    std::ostringstream ip;
    ip << node_.get_ip_addr();
    if (ip.str().empty()) {
        ip << "No response";
    }

    // FQDN
    std::ostringstream fqdn;
    fqdn << node_.get_fqdn();

    size_t max_len = ip.str().size();
    if (fqdn.str().size() > max_len) {
        max_len = fqdn.str().size();
    }

    size_t text_pos_x = x_ - ((max_len / 2) * 4.5);
    size_t text_pos_y = y_ + height_ + 20;

    alpha_ -= 0.0090;
    if (alpha_ < 0.0) {
        alpha_ = 0.0;
    }

    rc_->font_size(12);
    rc_->set_source_rgba(1, 1, 1, alpha_);
    if (fqdn.str().size() > 0) {
        rc_->move_to(text_pos_x , text_pos_y);
        rc_->show_text(fqdn.str());
        text_pos_y += 12 + 5;
    }
    rc_->move_to(text_pos_x , text_pos_y);
    rc_->show_text(ip.str());

    // Rectange line
    rc_->line_width(3);
    rc_->set_source_rgb(0.0, 0.0, 0.9);
    rc_->rectangle(x_, y_, width_, height_);
    rc_->stroke();
}

} // namespace vtr

