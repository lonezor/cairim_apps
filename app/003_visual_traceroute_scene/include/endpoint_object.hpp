#pragma once

#include <cairim/object.hpp>

namespace vtr {

class endpoint_object : public object
{
    public:
        endpoint_object(double x, double y, double width, double height,
            std::shared_ptr<rendering_context> rc, std::string svg_path);

        void set_description(std::string desc);

        void draw(frame_context& fc) override;
    private:
        double alpha_{1.0};
        std::string desc_;
};

} // namespace vtr

