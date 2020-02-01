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

#include <cairim/cairim.hpp>

#include "winter_scene.hpp"

constexpr auto program_name = "Winter Scene";

int main(int argc, char* argv[])
{
    auto rep_width = replay_width_4k;
    auto rep_height = replay_height_4k;

    /*** Create Cairim capture scene ***/

    auto window = std::shared_ptr<cairo_xlib_window>(new cairo_xlib_window(capture_width,
                                                                           capture_height,
                                                                           window_xpos,
                                                                           window_ypos,
                                                                           std::string(program_name),
                                                                           false));

    auto cap_rc = std::shared_ptr<rendering_context>(new rendering_context(window->get_surface(),
                                                                       window->get_context(),
                                                                       capture_width,
                                                                       capture_height,
                                                                       scale_ref_width,
                                                                       scale_ref_height,
                                                                       anti_aliasing::fast,
                                                                       nullptr));

    auto cap_scene = std::shared_ptr<scene>(new winter_scene(capture_width,
                                          capture_height,
                                          cap_rc,
                                          1001));

    /*** Create Cairim replay scene ***/

    auto image = cairo_image_surface(rep_width, rep_height);
    auto png_gen = std::shared_ptr<png_generator>(new png_generator(8, std::string(default_png_dir), png_compression_level_min));
    auto rep_rc  = std::shared_ptr<rendering_context>(new rendering_context(image.get_surface(),
                                                                        image.get_context(),
                                                                        rep_width,
                                                                        rep_height,
                                                                        scale_ref_width,
                                                                        scale_ref_height,
                                                                        anti_aliasing::best,
                                                                        png_gen));

    auto rep_scene = std::shared_ptr<scene>(new winter_scene(scale_ref_width,
                                                             scale_ref_height,
                                                             rep_rc,
                                                             2000));

    /*** Start Cairim (exit capture scene with ESC key) ***/
    return cairim_main(argc, argv, window, cap_scene, rep_scene, false);
}
