#include "snow_wheel.hpp"   
    
snow_wheel::snow_wheel(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
    std::string svg_path)
    : object(x,y,width,height, rc, svg_path) {

}

void snow_wheel::draw(frame_context& fc)
{
    static double rate = 0.001;
    if (intersects(fc.cursor_x, fc.cursor_y)) {
        
        if (button_active(fc.button_state, button::left)) {
            rate -= 0.0001;
        }
        if (button_active(fc.button_state, button::right)) {
            x_ = fc.cursor_x;
            y_ = fc.cursor_y;
        }
    } else {
        rate = 0.001;
    }

    static double a = 0;
    a -= rate;
    if (a < 0){
        a = 1;
    }

    draw_svg_surface(x_, y_, a * 2 * m_pi);
}

