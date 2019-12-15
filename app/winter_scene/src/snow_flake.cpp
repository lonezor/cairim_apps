#include "snow_flake.hpp"    
    
snow_flake::snow_flake(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path) {

}

void snow_flake::draw(frame_context& fc)
{

}

