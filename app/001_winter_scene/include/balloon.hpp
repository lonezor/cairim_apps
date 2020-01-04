#pragma once

#include <cairim/object.hpp>

class balloon : public object
{
    public:
        balloon(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

        void draw(frame_context& fc) override;
    private:
        double alpha_{1.0};
        double thrust_{0.0};
        
};