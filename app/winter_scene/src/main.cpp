#include <cairim/capture_handler.hpp>
#include <cairim/replay_handler.hpp>
#include <cairim/constants.hpp>

#include "winter_scene.hpp"

#if 0

enum
{
    LONG_OPTION_WEB_ADDRESS = 1000,
    OPTION_OFFLOAD_SERVER = 1001,
    OPTION_TEST_TIMEOUT = 1002,
    OPTION_DNS_SCALE_FACTOR = 1003,
    OPTION_OBJECT_SCALE_FACTOR = 1004,
    OPTION_RELAY_SHUTDOWN_TIMER = 1005,
    OPTION_REPLAY_SHUTDOWN_TIMER = 1006,
    OPTION_LOG_LEVEL = 1007,
    OPTION_HELP = 1008,
    OPTION_VERSION = 1009,
};

// clang-format off
static struct option long_options[] =
{
    {"scene",           required_argument, 0, OPTION_WEB_ADDRESS},
    {"capture",           no_argument, 0, OPTION_WEB_ADDRESS},
    {"capture-file",           required_argument, 0, OPTION_WEB_ADDRESS},
    {"output-dir",           required_argument, 0, OPTION_WEB_ADDRESS},
    {"replay",           no_argument, 0, OPTION_WEB_ADDRESS},
    {"replay-resolution",           required_argument, 0, OPTION_WEB_ADDRESS},
    {"concurrency",  required_argument, 0, OPTION_RELAY_SHUTDOWN_TIMER},
    {"nr-segments",        required_argument, 0, OPTION_OFFLOAD_SERVER},
    {"segment-idx",          required_argument, 0, OPTION_TEST_TIMEOUT},

    {"help",                  no_argument,       0, OPTION_HELP},
    {0,                       0,                 0, 0 }
};

static char* g_scene = nullptr;
static char* g_output_dir = nullptr;
static char* g_capture_file = nullptr;
static int g_replay_width = replay_width_2k;
static int g_Replay_height = replay_height_2k

void print_help() // TODO: move common options to library
{
    show-cursor
    show-osd
    show-screen-border
    std::cout << "Usage: cairim [OPTIONS]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " --scene=STRING               Scene to render: {water_mill, shell} - default: water_mill" << std::endl;
    std::cout << " --capture                    Capture requested. User input is recorded using X11 window" << std::endl;
    std::cout << " --capture-file=STRING        Path to recording (both capture/replay). Not mandatory if both capture/replay is requested" << std::endl;
    std::cout << " --output-dir=STRING          Output directory for PNG files - default '/tmp/cairim'" << std::endl;
    std::cout << " --replay                     Replay requested. High resolution rendering based on capture file" << std::endl;
    std::cout << " --replay-resolution=STRING   Screen resolution. Possible settings: {1k,2k,4k,8k} - default 2k" << std::endl;
    std::cout << " --concurrency=INTEGER        Number of concurrent rendering threads - default no concurrency (1)" << std::endl;
    std::cout << " --nr-segments=INTEGER        Number of rendering segments. This allows splitting up the work load over time and/or machines - default one" << std::endl;
    std::cout << " --segment-idx=INTEGER        Zero based rendering index in the range given by --nr-segments, e.g {0-9} for 10 segments" << std::endl;
    std::cout << " --help                       This help screen" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage examples:" << std::endl;
    std::cout << " 1) Capture/replay with default settings (press 'q' to close window)" << std::endl;
    std::cout << " cairim --capture --replay" << std::endl;
    std::cout << std::endl;
    std::cout << " 2) Capture to file. Then at a later time render 4k output" << std::endl;
    std::cout << " cairim --capture --capture-file/tmp/cairim/water_mill.cap" << std::endl;
    std::cout << " cairim --replay --capture-file/tmp/cairim/water_mill.cap --output-dir=/tmp/cairim/png --replay-resolution=4k" << std::endl;
    std::cout << std::endl;
    std::cout << " 3) Render farm setup" << std::endl;
    std::cout << " cairim --capture --capture-file=/mnt/nfs/cairim/water_mill.cap" << std::endl;
    std::cout << std::endl;
    std::cout << " Node #0-7:" << std::endl;
    std::cout << " cairim --replay --capture-file=/mnt/nfs/cairim/water_mill.cap --output-dir=/mnt/nfs/cairim/png --replay-resolution=8k" << std::endl
              <<   "--concurrency=6 --nr-segments=8 --segment-idx={0-7}" << std::endl;
    std::cout << std::endl;
}

#endif

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
                                          level_of_detail_capture));

    auto cap_handler = capture_handler(cap_scene, window, cap_rc);

    auto rep_width = replay_width_2k;
    auto rep_height = replay_height_2k;
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
                                                             level_of_detail_replay));
    
    

    // Capture user input until 'q' key is pressed
    auto frame_ctx_vector = cap_handler.run();

    // cap_handler.write_capture_file(frame_ctx_vector, "/tmp/out.cap");
    
    // Replay user input and render high resolution output
    auto rep_handler = replay_handler(rep_scene);
    rep_handler.run(frame_ctx_vector, "/home/png");

    return 0;
}
