#pragma once

#include <SFML/Graphics.hpp>
#include "i_trap_factory.hpp"
#include "i_tower_factory.hpp"

using namespace WVM;

class GTowerNode : public TowerNode{
public:
    std::string texture_path;
    GTowerNode(std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TowerNode&)> new_creator, 
            unsigned new_cost, const std::string& path_to_texture);
};

class GTrapNode : public TrapNode{
public:
    std::string texture_path;
    GTrapNode(std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TrapNode&)> new_creator, 
            unsigned new_max_level, unsigned new_cost, unsigned new_levelup_cost, const std::string& path_to_texture);
};