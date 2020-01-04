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

#pragma once

#include <cairim/object.hpp>
#include <list>

struct point_entry
{
    double x;
    double y;
};

class spiral : public object
{
    public:
        spiral(double x, double y, double width, double height, double velocity, double max_radius, std::shared_ptr<rendering_context> rc);

        void draw(frame_context& fc) override;
    private:
        point_entry new_point(double x, double y);

        double theta_{0};
        double radius_{0};
        double origo_x_;
        double origo_y_; 
        std::list<point_entry> points_;
        double velocity_;
        double max_radius_;
        bool shallow_;
};