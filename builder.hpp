#pragma once 

#include <network.hpp>

#include <vector>
#include <map>

namespace topo {

    enum class builder_type
    {
        script,
        run
    };

    int builder(topo::builder_type type, std::vector<Node> nodes);
    int builder_script(Topology ns);
    int builder_run(Topology ns);

    
} // namespace topo
