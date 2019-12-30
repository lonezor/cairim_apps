#include "star.hpp"    
#include <stdlib.h>
    
star::star(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{
    // Brightness animation based on size
    step_ = 0.0020 * (width);
}

void star::draw(frame_context& fc)
{
    // Let alpha continuously go down and up
    alpha_ -= step_;
    if (alpha_ < 0.5) {
        alpha_ = 0.5;
        step_ *= -1;
    } else if (alpha_ > 1.0) {
        alpha_ = 1.0;
        step_ *= -1;
    }

    draw_svg_surface(x_, y_, alpha_, 0.0);
}

