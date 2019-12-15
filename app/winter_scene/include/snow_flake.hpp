#pragma once

#include <cairim/object.hpp>

class snow_flake : public object
{
    public:
        snow_flake(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

        void draw(frame_context& fc) override;

    private:
    
};