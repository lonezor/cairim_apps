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

#include <cairim/object.hpp>

#include "node.hpp"

namespace vtr {

class node_object : public object
{
    public:
        node_object(double x, double y, double width, double height, node& node,
            std::shared_ptr<rendering_context> rc, std::string svg_path);

        void draw(frame_context& fc) override;

        void refresh_text_visibility();
    private:
        double alpha_{1.0};
        double velocity_x_{10};
        double velocity_y_{10};
        node node_;
};

} // namespace vtr