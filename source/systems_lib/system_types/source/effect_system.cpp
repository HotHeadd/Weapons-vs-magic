#include "effect_system.hpp"
#include "i_sys_manager.hpp"

namespace WVM
{

EffectSystem::EffectSystem(ISystemManager& manager) noexcept : manager_(manager) {}

void EffectSystem::update(){
    for (auto iter = targets_.begin(); iter != targets_.end();){
        std::weak_ptr<Effected> target = *iter;
        if (target.expired()){
            iter = targets_.erase(iter);
        }
        else{
            target.lock()->inflict_effects();
            ++iter;
        }
    }
}

void EffectSystem::refresh(){
    for (auto iter = targets_.begin(); iter != targets_.end();){
        std::weak_ptr<Effected> target = *iter;
        if (target.expired()){
            iter = targets_.erase(iter);
        }
        else{
            target.lock()->vanish_effects();
            ++iter;
        }
    }
}

bool EffectSystem::check_type(const Entity* ptr){
    return dynamic_cast<const Effected*>(ptr);
}


void EffectSystem::do_remove(std::shared_ptr<void> obj){
    std::shared_ptr<Effected> target = std::static_pointer_cast<Effected>(obj);
    auto iter = std::find_if(targets_.begin(), targets_.end(), [&obj](const std::weak_ptr<Effected>& x){return obj.get() == x.lock().get();});
    if (iter == targets_.end()){
        throw std::runtime_error("Do_remove in effect_system (why): No target in effect system");
    }
    targets_.erase(iter);
}

void EffectSystem::do_add(std::shared_ptr<void> obj){
    std::shared_ptr<Effected> target = std::static_pointer_cast<Effected>(obj);
    targets_.push_front(target);
}

bool EffectSystem::is_empty(){
    return targets_.empty();
}

} // namespace WVM
