#include "effect_creators.hpp"
#include "poisoning.hpp"
#include "weakening.hpp"
#include "slowdown.hpp"


std::shared_ptr<Effect> create_poisoning(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Poisoning>(target, strength, ticks);
}

std::shared_ptr<Effect> create_weakening(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Weakening>(target, strength, ticks);
}

std::shared_ptr<Effect> create_slowdown(std::shared_ptr<Effected> target){
    unsigned strength = 3;
    unsigned ticks = 15;
    return std::make_shared<Slowdown>(target, strength, ticks);
}