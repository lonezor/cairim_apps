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

#include <cairim/scene.hpp>
#include "snow_flake.hpp"   

class winter_scene : public scene
{
    public:
        winter_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail);

        void draw_main(frame_context& fc) override;
        void draw_snowflakes(frame_context& fc);

    private:
        std::vector<std::unique_ptr<object>> bg_objects_;
        std::vector<std::unique_ptr<snow_flake>> snow_flakes_;
        uint64_t frames_{0};
        
};

