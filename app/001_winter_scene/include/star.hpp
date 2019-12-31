#pragma once

#include <cairim/object.hpp>

class star : public object
{
    public:
        star(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

        void draw(frame_context& fc) override;
    private:
        double alpha_{1.0};
        double step_;
        
};