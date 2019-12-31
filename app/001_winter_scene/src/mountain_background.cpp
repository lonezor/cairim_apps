#include "mountain_background.hpp"   
    
mountain_background::mountain_background(double x, double y, double width, double height, 
double scroll_speed, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path) 
    , scroll_speed_(scroll_speed) {

}

void mountain_background::draw(frame_context& fc)
{
    x_ -= scroll_speed_;
    draw_svg_surface(x_, y_, 1.0, 0.0);
}

