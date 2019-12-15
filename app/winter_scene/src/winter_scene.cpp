#include "winter_scene.hpp"
#include "snow_wheel.hpp"

winter_scene::winter_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail)
    : scene(width, height, rc, level_of_detail)

{
    objects_.emplace_back(std::unique_ptr<object>(new snow_wheel(width/2,height/2,width/2, width/2, rc_, "/usr/local/share/winter_scene/snow_wheel.svg")));
}

void winter_scene::draw_main(frame_context& fc)
{
    fc.scene_width = width_;
    fc.scene_height = height_;

    rc_->set_source_rgb(0.2,0,0.2);
    rc_->paint();

    for(auto&& obj : objects_) {
        obj->draw(fc);
    }
}
