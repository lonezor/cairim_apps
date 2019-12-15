#pragma once

#include <cairim/object.hpp>

class snow_wheel : public object
{
    public:
        snow_wheel(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

         virtual void draw(frame_context& fc);

    private:
    
};