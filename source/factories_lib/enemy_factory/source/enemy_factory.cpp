#include "enemy_factory.hpp"

namespace WVM
{

std::shared_ptr<Entity> EnemyFactory::create_from_json(){
    return nullptr;
}

std::shared_ptr<Entity> EnemyFactory::create(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("Enemy cannot be created: no creator");
    }
    auto new_enemy = creators_[name](manager_, fact_manager_);
    new_enemy->set_type(name);
    return new_enemy;
}

void EnemyFactory::add_enemy(std::string name, std::function<std::shared_ptr<Entity>(ISystemManager&, IFactoryManager&)> creator){
    if (creators_.contains(name)){
        throw std::runtime_error("Enemy already in creators");
    }
    creators_.emplace(std::move(name), std::move(creator));
}

bool EnemyFactory::can_create(const std::string& name){
    return creators_.contains(name);
}

} // namespace WVM
