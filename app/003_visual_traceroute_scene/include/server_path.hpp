
#include <vector>
#include <arpa/inet.h>

#include "node.hpp"

namespace vtr {

constexpr int hop_limit_max = 255;

class server_path
{
    public:
        server_path(std::string fqdn);

        void discover(int max_hop_limit);
        void print();

    private:
        std::vector<node> path_;
        std::string server_ip_;
        std::string fqdn_;
        int af_{AF_INET};
};

} // namespace vtr