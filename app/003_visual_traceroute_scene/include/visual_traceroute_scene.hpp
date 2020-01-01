#pragma once

#include <memory>
#include <vector>

#include <cairim/scene.hpp>

#include "server_path.hpp"
#include "endpoint_object.hpp"
#include "node_object.hpp"

namespace vtr {

class visual_traceroute_scene : public scene
{
    public:
        visual_traceroute_scene(double width, double height, std::vector<std::shared_ptr<vtr::server_path>>& paths, 
            std::shared_ptr<rendering_context> rc, uint64_t level_of_detail);

        void draw_main(frame_context& fc) override;
        int get_node_y_pos(size_t hop_idx, size_t node_idx);

    private:
        std::vector<std::shared_ptr<vtr::server_path>> paths_;
        std::unique_ptr<endpoint_object> laptop_object_;
        std::unique_ptr<endpoint_object> server_object_;
        std::vector<std::unique_ptr<node_object>> node_objects_;
        std::vector<size_t> nodes_per_hop_;
        uint64_t frames_{0};
        std::string fqdn_;
        bool server_found_{false};

        // todo: map<> with key ip_fqdn -> node_object so that shared routes can be using the same object
};

} // namespace vtr