#pragma once

#include <cairim/object.hpp>

class mountain_background : public object
{
    public:
        mountain_background(double x, double y, double width, double height, double scroll_speed, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

         virtual void draw(frame_context& fc);

    private:
        double scroll_speed_{0.0};
};
