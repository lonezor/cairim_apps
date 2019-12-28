#include "winter_scene.hpp"
#include "snow_wheel.hpp"
#include "snow_flake.hpp"
#include "mountain_background.hpp"

winter_scene::winter_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail)
    : scene(width, height, rc, level_of_detail)

{
    double x = 1650;
    double y = 790;
    double w = width*4.7;
    double h = height;

    bg_objects_.emplace_back(std::unique_ptr<object>(new mountain_background(x,y, w, h, 0, rc_, 
        "/usr/local/share/winter_scene/mountain_background_00.svg")));
    bg_objects_.emplace_back(std::unique_ptr<object>(new mountain_background(x,y, w, h, 0.1, rc_, 
        "/usr/local/share/winter_scene/mountain_background_01.svg")));
    bg_objects_.emplace_back(std::unique_ptr<object>(new mountain_background(x,y, w, h, 0.2, rc_, 
        "/usr/local/share/winter_scene/mountain_background_02.svg")));
    bg_objects_.emplace_back(std::unique_ptr<object>(new mountain_background(x,y, w, h, 0.3, rc_, 
        "/usr/local/share/winter_scene/mountain_background_03.svg")));
}

void winter_scene::draw_snowflakes(frame_context& fc)
{
    for(int i=0; i < (int)5; i++) {
        double x = -10 + (drand48() * width_);
        double y = -1000 * drand48();
        double size = 0;
        while (size < 3) {
            size = drand48() * 7;
            if (size > 7) {
                size = 7;
            }
        } 
        
        snow_flakes_.emplace_back(std::unique_ptr<snow_flake>(new snow_flake(x,y, size, size, rc_, 
        "/usr/local/share/winter_scene/snow_flake.svg")));
    }

    for(auto it = snow_flakes_.begin() ; it !=  snow_flakes_.end(); it++) {
        auto sf_y = (*it)->get_y();
        auto sf_height = (*it)->get_height();

        (*it)->draw(fc);

        if (sf_y - sf_height > height_) {
            snow_flakes_.erase(it--);
            continue;
        }
    }
}

void winter_scene::draw_main(frame_context& fc)
{
    fc.scene_width = width_;
    fc.scene_height = height_;

    rc_->set_source_rgb(0.2,0,0.2);
    rc_->paint();

    for(auto&& obj : bg_objects_) {
        obj->draw(fc);
    }

    draw_snowflakes(fc);

}
