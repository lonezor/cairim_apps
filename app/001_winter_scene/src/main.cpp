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

#include <cairim/capture_handler.hpp>
#include <cairim/replay_handler.hpp>
#include <cairim/constants.hpp>
#include <cairim/png_generator.hpp>

#include "winter_scene.hpp"

// todo, move all common cairim code to library and just provide a cairim_main()
// with overall config. Super simple on application level
// cairim main can also handle argv to get common command line option interface

int main(int argc, char* argv[])
{
   // Create main window
    auto window = std::shared_ptr<cairo_xlib_window>(new cairo_xlib_window(capture_width,
                                                                           capture_height,
                                                                           window_xpos,
                                                                           window_ypos,
                                                                           "Winter Scene",
                                                                           false));

    // Define rendering context
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

    auto cap_handler = capture_handler(cap_scene, window, cap_rc);

    // Capture user input until ESC key is pressed
    auto frame_ctx_vector = cap_handler.run();

    cap_handler.write_capture_file(frame_ctx_vector, "/tmp/out.cap");

    auto rep_width = replay_width_2k;
    auto rep_height = replay_height_2k;
    auto image = cairo_image_surface(rep_width, rep_height);

    auto png_gen = std::shared_ptr<png_generator>(new png_generator(8, "/home/png", png_compression_level_min));

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

    
    // Replay user input and render high resolution output
    auto rep_handler = replay_handler(rep_scene);
    rep_handler.run(frame_ctx_vector, "/home/png");

    return 0;
}
