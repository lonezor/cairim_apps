#include "balloon.hpp"    
#include <stdlib.h>
    
balloon::balloon(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{

}

void balloon::draw(frame_context& fc)
{
    // Too low: force upwards
   if (y_ > 370) {
       thrust_ += 0.004;
   }

   // Too high: force downwards
   else if (y_ < 185) {
       thrust_ -= 0.004;
   }

    if (thrust_ < 0) {
        thrust_ = 0;
    } else if (thrust_ > 1) {
        thrust_ = 1;
    }

    x_ += 0.6 + thrust_;
    y_ += 0.5 - thrust_;
    
    draw_svg_surface(x_, y_, 0.95, 0.0);
}

