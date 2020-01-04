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

#pragma once

#include <cairim/object.hpp>

class snow_flake : public object
{
    public:
        snow_flake(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

        void draw(frame_context& fc) override;
        void highres_mode();

    private:
        double touch_force_{0};
        double velocity_[2];
        double angular_velocity_;
        double angle_{0};
        double wind_{0};
        bool highres_mode_{false};
};
