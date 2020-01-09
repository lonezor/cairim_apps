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

#include <memory>

#include <cairim/cairim.hpp>

#include "visual_traceroute_scene.hpp"
#include "server_path.hpp"

constexpr auto program_name = "Visual Traceroute Scene";

int main(int argc, char* argv[])
{
    /* For the test university networks in Sweden are used (listed roughly
     * in the order of size), which are stable domains and provide ideal
     * ICMP traceroute signaling.
     *
     * The servers are reachable using the traditional internet topology and are not
     * using anycast IP or any other mechanism to serve locally. This also includes
     * tunnelling of traffic as well as ICMP filtering which limits the effectiveness
     * of traceroute.
     * 
     * This visualiser intends to illustrate how the IP protocol itself works with a practical
     * example that is easy to understand, although it may not represent how the most popular
     * highly optimized web sites on the net are accessed. The need for long distance IP routing
     * however will not disappear completely.
     */
    std::vector<std::shared_ptr<vtr::server_path>> paths;
    //paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.sunet.se")));
    
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.su.se")));
    #if 0
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.gu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.uu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.lu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.lth.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.lnu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.umu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.liu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.mau.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.kth.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.hig.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.miun.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.du.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.oru.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.kau.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.mdh.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.ltu.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("www.hkr.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("ju.se")));
    paths.emplace_back(std::shared_ptr<vtr::server_path>(new vtr::server_path("chalmers.se")));
    #endif

    std::cout << "Starting traceroute" << std::endl;

    for(auto&& path : paths) {
        path->discover(64);
        path->print();
    }

    auto rep_width = replay_width_2k;
    auto rep_height = replay_height_2k;

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

    auto cap_scene = std::shared_ptr<scene>(new vtr::visual_traceroute_scene(capture_width,
                                          capture_height,
                                          paths,
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

    auto rep_scene = std::shared_ptr<scene>(new vtr::visual_traceroute_scene(scale_ref_width,
                                                             scale_ref_height,
                                                             paths,
                                                             rep_rc,
                                                             2000));                                    

    /*** Start Cairim (exit capture scene with ESC key) ***/
    return cairim_main(argc, argv, window, cap_scene, rep_scene, false);
}
