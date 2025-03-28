#pragma once

#include "effect.hpp"
#include <unordered_set>
#include <memory>

namespace WVM
{   

class Effected{
public:
    virtual ~Effected() = default;
    virtual std::unordered_set<std::shared_ptr<Effect>>& effects();
    virtual void inflict_effects();
    virtual void add_effect (std::shared_ptr<Effect> effect);
    virtual void remove_effect(std::shared_ptr<Effect> effect);
    virtual void vanish_effects();
protected:
    std::unordered_set<std::shared_ptr<Effect>> effects_; 
};

} // namespace WVM
