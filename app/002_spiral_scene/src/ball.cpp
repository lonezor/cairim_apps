#include "ball.hpp"    
#include <stdlib.h>
    
ball::ball(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{
}

void ball::draw(frame_context& fc)
{
    x_ += velocity_x_;
    y_ += velocity_y_;
    if (x_ > fc.scene_width || x_ < 0) {
        velocity_x_ *= -1;
    }
    if (y_ > fc.scene_height || y_ < 0) {
        velocity_y_ *= -1;
    }

    draw_svg_surface(x_, y_, 1.0, 0.0);
}

