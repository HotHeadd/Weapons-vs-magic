#include "effected.hpp"
namespace WVM
{

void Effected::inflict_effects(){
    for (auto iter = effects_.begin(); iter != effects_.end();){
        std::shared_ptr<Effect> effect = *iter;
        ++iter;
        if (effect->turns_to_last() == 0){
            remove_effect(effect);
        }
        else{
            effect->inflict();
        }
    }
}

void Effected::add_effect(std::shared_ptr<Effect> effect){
    if (effects_.contains(effect)){
        throw std::runtime_error("Add effect: Effect is already in applied effects");
    }
    effects_.insert(effect);
}

void Effected::remove_effect(std::shared_ptr<Effect> effect){
    if (!effects_.contains(effect)){
        throw std::runtime_error("Remove effect: No effect in applied effects");
    }
    effect->neutralize();
    effects_.erase(effect);
}

void Effected::vanish_effects(){
    for (auto& effect : effects_){
        effect->neutralize();
    }
    effects_.clear();
}

std::unordered_set<std::shared_ptr<Effect>>& Effected::effects(){
    return effects_;
}

} // namespace WVM
