#pragma once

#include "i_enemy_factory.hpp"
#include "i_enemy.hpp"
#include <string>
#include <unordered_map>
#include <functional>

namespace WVM
{

class EnemyFactory : public IEnemyFactory{
public:
    explicit EnemyFactory(ISystemManager& manager, IFactoryManager& fact_manager) : manager_(manager), fact_manager_(fact_manager) {}
    std::shared_ptr<Entity> create_from_json() override;
    std::shared_ptr<Entity> create(const std::string& name) override;

    void add_enemy(std::string name, std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&)> creator) override;

    bool can_create(const std::string& name) override;
private:
    ISystemManager& manager_;
    IFactoryManager& fact_manager_;
    std::unordered_map<std::string, std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&)>> creators_;
};

} // namespace WVM