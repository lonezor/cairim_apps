

#include "visual_traceroute_scene.hpp"

visual_traceroute_scene::visual_traceroute_scene(double width, double height,
    std::shared_ptr<rendering_context> rc, uint64_t level_of_detail)
    : scene(width, height, rc, level_of_detail)
{
}

void visual_traceroute_scene::draw_main(frame_context& fc)
{
    fc.scene_width = width_;
    fc.scene_height = height_;

}
