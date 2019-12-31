#pragma once

#include <cairim/scene.hpp>
#include "snow_flake.hpp"   

class winter_scene : public scene
{
    public:
        winter_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail);

        void draw_main(frame_context& fc) override;
        void draw_snowflakes(frame_context& fc);

    private:
        std::vector<std::unique_ptr<snow_flake>> snow_flakes_;
        std::vector<std::unique_ptr<object>> bg_objects_;
};

