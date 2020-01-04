/*
 *  Cairim App: Visual Traceroute Scene
 *  Copyright (C) 2020 Johan Norberg <lonezor@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>
 */

#include "visual_traceroute_scene.hpp"
#include "node_object.hpp"

namespace vtr {

visual_traceroute_scene::visual_traceroute_scene(double width, double height,
    std::vector<std::shared_ptr<vtr::server_path>>& paths,
    std::shared_ptr<rendering_context> rc, uint64_t level_of_detail)
    : scene(width, height, rc, level_of_detail)
    , paths_(paths)
{
    int x = 175;
    int y = -1;

    for(auto&& path : paths_) {
        auto nodes = path->get_nodes();
        fqdn_ = path->get_fqdn();
        for (auto&& node : nodes) {
            nodes_per_hop_.emplace_back(1);
            int y = get_node_y_pos(0, 0);
            node_objects_.emplace_back(std::unique_ptr<node_object>(new node_object(x,y, 30, 30, node, rc_, "")));
            x += 80;

        }
        break;
    }

    y = get_node_y_pos(0, 0);
    laptop_object_ = std::unique_ptr<endpoint_object>(new endpoint_object(75, y + 22, 50, 50,
                                                    rc_, "/usr/local/share/visual_traceroute_scene/laptop.svg"));
    server_object_ = std::unique_ptr<endpoint_object>(new endpoint_object(width_ - 75, y + 22, 100, 100,
                                                    rc_, "/usr/local/share/visual_traceroute_scene/server.svg"));
}

int visual_traceroute_scene::get_node_y_pos(size_t hop_idx, size_t node_idx)
{
    auto hops = nodes_per_hop_.size();
    if (hop_idx > hops) {
        return -1;
    }

    auto nodes = static_cast<double>(nodes_per_hop_[hop_idx]);
    if (node_idx > nodes) {
        return -1;
    }

    double y_pos = height_ / (nodes + 1);

    return y_pos;
}

void visual_traceroute_scene::draw_main(frame_context& fc)
{
    fc.scene_width = width_;
    fc.scene_height = height_;

    rc_->set_source_rgb(0, 0, 0);
    rc_->paint();

    laptop_object_->draw(fc);
    laptop_object_->set_description(fqdn_);

    size_t node_idx = 0;

    if (!server_found_) {
        uint64_t nr_nodes = frames_ / 130;
        if (nr_nodes < 1) {
            nr_nodes = 1;
        }
        
        for(auto&& no : node_objects_) {
            no->draw(fc);
            nr_nodes--;
            if (nr_nodes <= 0) {
                break;
            }

            if (node_idx++ == node_objects_.size() - 1) {
                server_found_ = true;
                frames_ = 0;
                break;
            }
        }
    } else {
        for(auto&& no : node_objects_) {
            no->draw(fc);
        }
        if (frames_ > 60) {
            server_object_->draw(fc);
        }
    }

    frames_++;
}

} // namespace vtr
