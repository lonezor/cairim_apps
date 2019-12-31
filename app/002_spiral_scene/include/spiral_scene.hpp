#pragma once

#include <cairim/scene.hpp>
#include <list>
#include "ball.hpp"
#include "spiral.hpp"
#include <memory>



class spiral_scene : public scene
{
    public:
        spiral_scene(double width, double height, std::shared_ptr<rendering_context> rc, uint64_t level_of_detail);

        void draw_main(frame_context& fc) override;

    private:
        std::vector<std::unique_ptr<spiral>> spirals_;
        std::vector<std::unique_ptr<ball>> balls_;
};

