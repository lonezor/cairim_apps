#pragma once

#include <cairim/scene.hpp>

class visual_traceroute_scene : public scene
{
    public:
        visual_traceroute_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail);

        void draw_main(frame_context& fc) override;

    private:
};

