#include "trap_factory.hpp"

namespace WVM
{

std::shared_ptr<Entity> TrapFactory::create_from_json(){
    return nullptr;
}

void TrapFactory::add_trap(std::string name, std::unique_ptr<TrapNode> node){
    if (creators_.contains(name)){
        throw std::runtime_error("Trap is already in creators");
    }
    creators_[name] = std::move(node);
}

std::shared_ptr<Entity> TrapFactory::create(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("Trap is not in creators");
    }
    TrapNode& node = *(creators_[name]);
    auto new_trap = node.creator(manager_, fact_manager_, node);
    new_trap->set_type(name);
    return new_trap;
}

void TrapFactory::levelup_trap(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("No trap of this kind to levelup");
    }
    TrapNode& node = *(creators_[name]);
    if (node.trap_level == node.max_level){
        throw std::runtime_error("Trap is already at max level");
    }
    node.trap_level += 1;
    node.levelup_cost *= 1.5;
}

unsigned TrapFactory::get_level(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("No trap of this kind to get level");
    }
    return creators_[name]->trap_level;
}
unsigned TrapFactory::get_max_level(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("No trap of this kind to get max level");
    }
    return creators_[name]->max_level;
}

unsigned TrapFactory::get_cost(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("No trap of this kind to get cost");
    }
    return creators_[name]->cost;
}

unsigned TrapFactory::get_levelup_cost(const std::string& name){
    if (!creators_.contains(name)){
        throw std::runtime_error("No trap of this kind to get levelup cost");
    }
    return creators_[name]->levelup_cost;
}

bool TrapFactory::can_create(const std::string& name){
    return creators_.contains(name);
}

std::unordered_map<std::string, std::unique_ptr<TrapNode>>& TrapFactory::creators(){
    return creators_;
}

} // namespace WVM
