#pragma once

#include <cairim/object.hpp>

class ball : public object
{
    public:
        ball(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

        void draw(frame_context& fc) override;
    private:
        double alpha_{1.0};
        double velocity_x_{10};
        double velocity_y_{10};
};