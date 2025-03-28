#include "tower_factory.hpp"

namespace WVM
{

std::shared_ptr<Entity> TowerFactory::create_from_json(){
    return nullptr;
}

std::shared_ptr<Entity>TowerFactory::create(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("Tower cannot be created: no creator");
    }
    TowerNode& node = *(creators_[name].get());
    auto new_tower = node.creator(manager_, fact_manager_, node);
    new_tower->set_type(name);
    return new_tower;
}

void TowerFactory::add_tower(std::string name, std::unique_ptr<TowerNode> node){
    if (creators_.contains(name)){
        throw std::runtime_error("Tower already in creators");
    }
    creators_[name] = std::move(node);
}

bool TowerFactory::can_create(const std::string& name){
    return creators_.contains(name);
}

unsigned TowerFactory::get_cost(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("No tower to get cost in factory");
    }
    return creators_[name]->cost;
}

std::unordered_map<std::string, std::unique_ptr<TowerNode>>& TowerFactory::creators(){
    return creators_;
}

} // namespace WVM
