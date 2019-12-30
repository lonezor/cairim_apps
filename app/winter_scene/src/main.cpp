#include <cairim/capture_handler.hpp>
#include <cairim/replay_handler.hpp>
#include <cairim/constants.hpp>

#include "winter_scene.hpp"

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
                                                                       anti_aliasing::fast));

    auto cap_scene = std::shared_ptr<scene>(new winter_scene(capture_width,
                                          capture_height,
                                          cap_rc,
                                          1001));

    auto cap_handler = capture_handler(cap_scene, window, cap_rc);

    auto rep_width = replay_width_8k;
    auto rep_height = replay_height_8k;
    auto image = cairo_image_surface(rep_width, rep_height);

    auto rep_rc  = std::shared_ptr<rendering_context>(new rendering_context(image.get_surface(),
                                                                        image.get_context(),
                                                                        rep_width,
                                                                        rep_height,
                                                                        scale_ref_width,
                                                                        scale_ref_height,
                                                                        anti_aliasing::best));

    auto rep_scene = std::shared_ptr<scene>(new winter_scene(scale_ref_width,
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
