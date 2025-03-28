#include "lair_system.hpp"

namespace WVM
{

LairSystem::LairSystem(ISystemManager& manager) noexcept : manager_(manager) {}


void LairSystem::update(){
    for (auto& lair : lairs_){
        lair->update();
    }
}

void LairSystem::refresh(){
    for (auto& lair : lairs_){
        lair->wave_up();
    }
}

bool LairSystem::check_type(const Entity* ptr){
    return dynamic_cast<const ILair*>(ptr) != nullptr;
}

void LairSystem::do_remove(std::shared_ptr<void> obj){
    std::shared_ptr<ILair> lair = std::static_pointer_cast<ILair>(obj);
    if (!lairs_.contains(lair)){
        throw std::runtime_error("lair not in lairs");
    }
    lair->on_death();
    lairs_.erase(lair);
}

void LairSystem::do_add(std::shared_ptr<void> obj){
    std::shared_ptr<ILair> lair = std::static_pointer_cast<ILair>(obj);
    if (lairs_.contains(lair)){
        throw std::runtime_error("lair already in lairs");
    }
    lairs_.insert(lair);
}

bool LairSystem::is_empty(){
    for (auto& lair : lairs_){
        if (!lair->no_enemies_left()){
            return false;
        }
    }
    return true;
}

std::unordered_set<std::shared_ptr<ILair>>& LairSystem::get_lairs(){
    return lairs_;
}

} // namespace WVM
