#include "g_nodes.hpp"

GTowerNode::GTowerNode(std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TowerNode&)> new_creator, 
            unsigned new_cost, const std::string& path_to_texture) : TowerNode(new_creator, new_cost),
            texture_path(path_to_texture) {}

GTrapNode::GTrapNode(std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TrapNode&)> new_creator, 
            unsigned new_max_level, unsigned new_cost, unsigned new_levelup_cost, const std::string& path_to_texture) :
                TrapNode(new_creator, new_max_level, new_cost, new_levelup_cost), texture_path(path_to_texture) {}