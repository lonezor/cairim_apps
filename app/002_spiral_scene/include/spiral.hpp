#pragma once

#include <cairim/object.hpp>
#include <list>

struct point_entry
{
    double x;
    double y;
};

class spiral : public object
{
    public:
        spiral(double x, double y, double width, double height, double velocity, double max_radius, std::shared_ptr<rendering_context> rc);

        void draw(frame_context& fc) override;
    private:
        point_entry new_point(double x, double y);

        double theta_{0};
        double radius_{0};
        double origo_x_;
        double origo_y_; 
        std::list<point_entry> points_;
        double velocity_;
        double max_radius_;
        bool shallow_;
};