#pragma once

#include "../traits/entity.hpp"
#include <memory>
#include "../object_interfaces/i_sys_manager.hpp"
#include <functional>


namespace WVM
{

class IFactoryManager;

class TrapNode{
public:
    std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TrapNode&)> creator;
    unsigned trap_level=1;
    unsigned max_level;
    unsigned cost;
    unsigned levelup_cost;
    TrapNode() {}
    TrapNode(std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&, TrapNode&)> new_creator, 
                   unsigned new_max_level, unsigned new_cost, unsigned new_levelup_cost){
        creator = new_creator;
        max_level = new_max_level;
        cost = new_cost;
        levelup_cost = new_levelup_cost;
    }
};

class ITrapFactory {
public:
    virtual std::shared_ptr<Entity> create_from_json() = 0;
    virtual std::shared_ptr<Entity> create(const std::string& name) = 0;

    virtual void add_trap(std::string name, std::unique_ptr<TrapNode>) = 0;
    virtual bool can_create(const std::string& name) = 0;


    virtual void levelup_trap(const std::string& name) = 0;

    virtual unsigned get_cost(const std::string& name) = 0;
    virtual unsigned get_levelup_cost(const std::string& name) = 0;
    virtual unsigned get_level(const std::string& name) = 0;
};

} // namespace WVM