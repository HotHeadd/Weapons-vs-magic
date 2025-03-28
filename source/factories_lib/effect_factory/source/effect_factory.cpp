#include "effect_factory.hpp"

namespace WVM
{

std::shared_ptr<Effect> EffectFactory::create_from_json(){
    return nullptr;
}

std::shared_ptr<Effect> EffectFactory::create(const std::string& name, std::shared_ptr<Effected> target){
    if (!creators_.contains(name)){
        throw std::runtime_error("Effect is not available in creators");
    }
    auto new_effect = creators_[name](std::move(target));
    new_effect->set_type(name);
    return new_effect;
}

void EffectFactory::add_effect(std::string name, std::function<std::shared_ptr<Effect>(std::shared_ptr<Effected>)> creator){
    if (creators_.contains(name)){
        throw std::runtime_error("Effect is already in creators");
    }
    creators_.emplace(std::move(name), std::move(creator));
}

bool EffectFactory::can_create(const std::string& name){
    return creators_.contains(name);
}

} // namespace WVM
