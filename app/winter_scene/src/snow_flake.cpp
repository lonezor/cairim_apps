#include "snow_flake.hpp"    
#include <stdlib.h>
    
snow_flake::snow_flake(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path) {
            double width_squared = width*width;
                velocity_[0] = 0;
                velocity_[1] = (1 / width_squared) * 50;
}

void snow_flake::highres_mode()
{
    highres_mode_ = true;
}

void snow_flake::draw(frame_context& fc)
{
    wind_ += 0.01;
    if (wind_ < 0){
        wind_ = 1;
    }

    velocity_[0] = wind_;
    x_ += velocity_[0];
    y_ += velocity_[1] - touch_force_;

    if (highres_mode_) {
        angle_ -= 0.01;
        if (angle_ < 0){
            angle_ = 1;
        }
        draw_svg_surface(x_, y_, 1.0, angle_ * 2 * m_pi);
    } else {
        rc_->set_source_rgba(1, 1, 1, 1);
        rc_->arc(x_, y_, width_, 1.0, 2 * m_pi);
        rc_->fill();
    }
}

