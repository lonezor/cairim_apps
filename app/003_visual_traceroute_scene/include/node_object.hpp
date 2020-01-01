#pragma once

#include <cairim/object.hpp>

#include "node.hpp"

namespace vtr {

class node_object : public object
{
    public:
        node_object(double x, double y, double width, double height, node& node,
            std::shared_ptr<rendering_context> rc, std::string svg_path);

        void draw(frame_context& fc) override;

        void refresh_text_visibility();
    private:
        double alpha_{1.0};
        double velocity_x_{10};
        double velocity_y_{10};
        node node_;
};

} // namespace vtr