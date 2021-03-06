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

#include "spiral_scene.hpp"

spiral_scene::spiral_scene(double width, double height,
    std::shared_ptr<rendering_context> rc, uint64_t level_of_detail)
    : scene(width, height, rc, level_of_detail)
{
    /* Add center spiral and four surrounding spirals
     *
     * They are deliberately kept small since the opposite can
     * be too much for the viewer, the pattern is by definition
     * very regular.
     */
    spirals_.emplace_back(std::unique_ptr<spiral>(new spiral(width_ / 2, height_ / 2, 10, 10, 0.10, 48.7, rc_)));
    spirals_.emplace_back(std::unique_ptr<spiral>(new spiral(width_ / 4, height_ / 4, 10, 10, 0.03, 38.5, rc_)));
    spirals_.emplace_back(std::unique_ptr<spiral>(new spiral(width_ / 4, 3 * (height_ / 4), 10, 10, 0.03, 38.5, rc_)));
    spirals_.emplace_back(std::unique_ptr<spiral>(new spiral(3 * (width_ / 4), height_ / 4, 10, 10, 0.03, 38.5, rc_)));
    spirals_.emplace_back(std::unique_ptr<spiral>(new spiral(3 * (width_ / 4), 3 * (height_ / 4), 10, 10, 0.03, 38.5, rc_)));
}

void spiral_scene::draw_main(frame_context& fc)
{
    fc.scene_width = width_;
    fc.scene_height = height_;

    if (balls_.size() < 20) {
        double v = drand48();
        if (v < 0.01) {
            double x = 1;
            double y = drand48() * 300;
            balls_.emplace_back(std::unique_ptr<ball>(new ball(x,y, 25, 25, rc_,
                "/usr/local/share/spiral_scene/ball.svg")));
        }
    }

    for(auto&& b : balls_) {
        b->draw(fc);

        // TODO: collision detection with knowledge about the balls direction so that
        //       a correct bouncing effect can be calculated
    }
    
    for(auto&& s : spirals_) {
        s->draw(fc);
    }
}
