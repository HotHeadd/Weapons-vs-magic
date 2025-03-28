#include "magic.hpp"

namespace WVM
{

void Magic::cast_spell(std::shared_ptr<Effected> target){
    for (auto& effect_pair : magic_effects_){
        std::shared_ptr<Effect> effect = factory_.create(effect_pair.first, target);
        effect->set_strength(effect_pair.second.e_strength);
        effect->set_duration(effect_pair.second.e_duration);
        target->add_effect(effect);
    }
}

void Magic::add_magic_effect(std::string e_name, unsigned e_strength, unsigned e_duration){
    if (magic_effects_.contains(e_name)){
        throw std::runtime_error("Add magic effect: effect is already in magic");
    }
    magic_effects_.emplace(std::move(e_name), MagicNode{e_strength, e_duration});
}

void Magic::remove_magic_effect(const std::string& e_name){
    if (!magic_effects_.contains(e_name)){
        throw std::runtime_error("Remove magic effect: no effect to remove from magic");
    }
    magic_effects_.erase(e_name);
}

std::unordered_map<std::string, MagicNode>& Magic::magic_effects(){
    return magic_effects_;
}

} // namespace WVM
