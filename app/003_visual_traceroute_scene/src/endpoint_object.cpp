#include <stdlib.h>

#include "endpoint_object.hpp"

namespace vtr {
    
endpoint_object::endpoint_object(double x, double y, double width, double height,
    std::shared_ptr<rendering_context> rc, std::string svg_path)
    : object(x,y,width,height, rc, svg_path)
{

}

void endpoint_object::set_description(std::string desc)
{
    desc_ = desc;
}

void endpoint_object::draw(frame_context& fc)
{
    if (!desc_.empty()) {
        double middle_pos = static_cast<double>(desc_.size()) / 2;
        size_t text_pos_x = x_ - (middle_pos * 7);
        size_t text_pos_y = y_ + (height_ / 2) + 5;

        rc_->set_source_rgba(1, 1, 1, 1);
        rc_->font_size(12);
        rc_->move_to(text_pos_x, text_pos_y);
        rc_->show_text(desc_);
    }

    draw_svg_surface(x_, y_, 1.0, 0.0);
}

} // namespace vtr
