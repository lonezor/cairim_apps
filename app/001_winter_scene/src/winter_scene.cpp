#include "winter_scene.hpp"
#include "snow_flake.hpp"
#include "mountain_background.hpp"
#include "star.hpp"

winter_scene::winter_scene(double width, double height,
    std::shared_ptr<rendering_context> rc, uint64_t level_of_detail)
    : scene(width, height, rc, level_of_detail)
{
    // Background
    double x = width / 2;
    double y = width / 2;
    double w = width;
    double h = height;
    bg_objects_.emplace_back(std::unique_ptr<object>(new mountain_background(x,y, w, h, 0, rc_, 
        "/usr/local/share/winter_scene/mountain_background.svg")));

    // Stars (not positioned in front of mountains)
    std::string star_svg_path = "/usr/local/share/winter_scene/star.svg";
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(60,102, 5, 5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(120,30, 5, 5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(240,290, 3.5, 3.5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(302,150, 4, 4, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(490,430, 2.5, 2.5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(550,88, 2.5, 2.5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(660,92, 5, 5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(800,340, 4, 4, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(920,66, 4, 4, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(1232,439, 5, 5, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(1302,120, 4, 4, rc_, star_svg_path)));
    bg_objects_.emplace_back(std::unique_ptr<object>(new star(1400,44, 3, 3, rc_, star_svg_path)));
}

void winter_scene::draw_snowflakes(frame_context& fc)
{
    double x = -200 + (drand48() * width_);
    double y = -6000 * drand48(); // delay snow animation on screen
    double size = 0;

    while (size < 3) {
        size = drand48() * 5;
        if (size > 5) {
            size = 5;
        }
    }

    for(int i=0; i < 2; i++) {
        auto sf = std::unique_ptr<snow_flake>(new snow_flake(x,y, 
            size, size, rc_, "/usr/local/share/winter_scene/snow_flake.svg"));

        // Currently two levels
        if (level_of_detail_ > 1000) {
            sf->highres_mode();
        }

        snow_flakes_.emplace_back(std::move(sf));
    }

    for(auto it = snow_flakes_.begin() ; it !=  snow_flakes_.end(); it++) {

        (*it)->draw(fc);

        auto sf_y = (*it)->get_y();
        auto sf_height = (*it)->get_height();

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
