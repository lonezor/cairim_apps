#include <memory>

#include <cairim/capture_handler.hpp>
#include <cairim/replay_handler.hpp>
#include <cairim/constants.hpp>

#include "visual_traceroute_scene.hpp"
#include "server_path.hpp"


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
    std::vector<std::unique_ptr<vtr::server_path>> paths;
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.sunet.se")));
    #if 0
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.su.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.gu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.uu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.lu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.lth.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.lnu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.umu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.liu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.mau.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.kth.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.hig.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.miun.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.du.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.oru.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.kau.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.mdh.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.ltu.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("www.hkr.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("ju.se")));
    paths.emplace_back(std::unique_ptr<vtr::server_path>(new vtr::server_path("chalmers.se")));
    #endif

    std::cout << "Starting traceroute" << std::endl;

    for(auto&& path : paths) {
        path->discover(64);
        path->print();
    }



    
    
    
    
    
    



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
                                                                       anti_aliasing::fast));

    auto cap_scene = std::shared_ptr<scene>(new visual_traceroute_scene(capture_width,
                                          capture_height,
                                          cap_rc,
                                          1001));

    auto cap_handler = capture_handler(cap_scene, window, cap_rc);

    auto rep_width = replay_width_1k;
    auto rep_height = replay_height_1k;
    auto image = cairo_image_surface(rep_width, rep_height);

    auto rep_rc  = std::shared_ptr<rendering_context>(new rendering_context(image.get_surface(),
                                                                        image.get_context(),
                                                                        rep_width,
                                                                        rep_height,
                                                                        scale_ref_width,
                                                                        scale_ref_height,
                                                                        anti_aliasing::best));

    auto rep_scene = std::shared_ptr<scene>(new visual_traceroute_scene(scale_ref_width,
                                                             scale_ref_height,
                                                             rep_rc,
                                                             2000));
    // Capture user input until ESC key is pressed
    auto frame_ctx_vector = cap_handler.run();

    cap_handler.write_capture_file(frame_ctx_vector, "/tmp/out.cap");
    
    // Replay user input and render high resolution output
    auto rep_handler = replay_handler(rep_scene);
    rep_handler.run(frame_ctx_vector, "/home/png");

    return 0;
}
