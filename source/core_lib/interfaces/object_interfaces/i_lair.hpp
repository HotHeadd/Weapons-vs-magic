#pragma once

#include "i_enemy.hpp"
#include "persistable.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace WVM
{

using cooldown_t = unsigned;
using amount_t = size_t;

struct LairNode{
    amount_t amount;
    cooldown_t cooldown;
    cooldown_t current_cooldown=0;
    amount_t current_amount;
    LairNode(amount_t amount_in, cooldown_t cooldown_in){
        amount = amount_in;
        current_amount = amount_in;
        cooldown = cooldown_in;
    }
};

class ILair : public Entity, public Persistable{
public:
    virtual bool no_enemies_left() = 0;
    virtual void wave_up() = 0;
    virtual void add_spawn_instructions(std::vector<std::unordered_map<std::string, LairNode>>) = 0;

    virtual std::vector<std::unordered_map<std::string, LairNode>>& spawn_instructions() = 0;
protected:
};

} // namespace WVM