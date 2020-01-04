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

#include <cairim/scene.hpp>
#include <list>
#include "ball.hpp"
#include "spiral.hpp"
#include <memory>



class spiral_scene : public scene
{
    public:
        spiral_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail);

        void draw_main(frame_context& fc) override;

    private:
        std::vector<std::unique_ptr<spiral>> spirals_;
        std::vector<std::unique_ptr<ball>> balls_;
};

