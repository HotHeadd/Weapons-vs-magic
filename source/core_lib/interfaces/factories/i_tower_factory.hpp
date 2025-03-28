#pragma once

#include "../traits/entity.hpp"
#include <memory>
#include "../object_interfaces/i_sys_manager.hpp"
#include <functional>


namespace WVM
{

class IFactoryManager;

class TowerNode{
public:
    std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TowerNode&)> creator;
    unsigned cost;
    TowerNode(std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TowerNode&)> new_creator, unsigned new_cost) :
    creator(new_creator), cost(new_cost) {}
};

class ITowerFactory {
public:
    virtual std::shared_ptr<Entity> create_from_json() = 0;
    virtual std::shared_ptr<Entity> create(const std::string& name) = 0;

    virtual void add_tower(std::string name, std::unique_ptr<TowerNode>) = 0;
    virtual bool can_create(const std::string& name) = 0;
    virtual unsigned get_cost(const std::string& name) = 0;
};

} // namespace WVM