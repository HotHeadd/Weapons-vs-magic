#pragma once

#include "../traits/entity.hpp"
#include <memory>
#include "../object_interfaces/i_sys_manager.hpp"

namespace WVM
{

class IFactoryManager;

class IEnemyFactory {
public:
    virtual std::shared_ptr<Entity> create_from_json() = 0;
    virtual std::shared_ptr<Entity> create(const std::string& name) = 0;

    virtual void add_enemy(std::string name, std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&)> creator) = 0;
    virtual bool can_create(const std::string& name) = 0;
};

} // namespace WVM
