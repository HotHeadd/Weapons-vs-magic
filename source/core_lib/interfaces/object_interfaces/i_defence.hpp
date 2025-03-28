#pragma once

#include "../traits/entity.hpp"
#include "i_enemy.hpp"
#include "shooting.hpp"
#include <vector>
#include <optional>
#include <string_view>

namespace WVM
{

class IDefence : public Effected, public Entity{
public:
    virtual void sell() = 0;

    virtual unsigned cost() = 0;

    virtual void reset_cooldown() = 0;
    virtual bool is_dead() = 0;
protected:
    virtual void provide_targets(std::vector<std::shared_ptr<Entity>>& targets) = 0;
    virtual void affect_target(std::shared_ptr<Entity> target) = 0;
};
    
} // namespace WVM
