#pragma once

#include "layout.hpp"
#include "i_enemy.hpp"
#include "i_defence.hpp"
#include "i_system.hpp"
#include "castle.hpp"

#include <map>
#include <memory>

namespace WVM
{

enum class SystemTag{
    EFFECT,
    DEFENCE,
    ENEMY,
    LAIR
};


class ISystemManager{
public:
    using ManagerIterator = std::map<SystemTag, std::shared_ptr<ISystem>>::iterator;
    virtual ~ISystemManager() = default;

    virtual ManagerIterator begin() = 0;
    virtual ManagerIterator end() = 0;

    virtual std::unordered_set<std::shared_ptr<IDefence>>& get_defence() = 0;
    virtual std::unordered_set<std::shared_ptr<IEnemy>>& get_enemies() = 0;
    virtual Castle& get_castle() = 0;
    virtual Layout& get_layout() = 0;
    virtual ISystem& get_system(SystemTag tag) = 0;
private:
};

} // namespace WVM