#pragma once

#include "effected.hpp"
#include <unordered_map>
#include <memory>
#include "i_effect_factory.hpp"

namespace WVM
{

struct MagicNode{
    unsigned e_strength;
    unsigned e_duration;
};

class Magic{
public:
    explicit Magic(IEffectFactory& factory) : factory_(factory) {}

    virtual void cast_spell(std::shared_ptr<Effected> target);
    virtual void add_magic_effect(std::string e_name, unsigned e_strength, unsigned e_duration);
    virtual void remove_magic_effect(const std::string& e_name);
    std::unordered_map<std::string, MagicNode>& magic_effects();
protected:
    IEffectFactory& factory_;
    std::unordered_map<std::string, MagicNode> magic_effects_;
};

} // namespace WVM
