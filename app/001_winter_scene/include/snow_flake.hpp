#pragma once

#include <cairim/object.hpp>



class snow_flake : public object
{
    public:
        snow_flake(double x, double y, double width, double height, std::shared_ptr<rendering_context> rc,
        std::string svg_path);

        void draw(frame_context& fc) override;
        void highres_mode();

    private:
        double touch_force_{0};
        double velocity_[2];
        double angular_velocity_;
        double angle_{0};
        double wind_{0};
        bool highres_mode_{false};
};
