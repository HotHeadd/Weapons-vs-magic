#pragma once

#include "i_defence.hpp"
#include <string>
#include <unordered_map>

namespace WVM
{   

enum class Strategy{
    FARTHEST_FROM_CASTLE,
    CLOSEST_TO_CASTLE,
    WEAKEST,
    HEALTHIEST,
    FASTEST,
};

class ITower : public IDefence, public Damagable{
public:
    virtual void level_up() = 0;

    virtual unsigned level() = 0;
    virtual double rapidity() = 0;
    virtual unsigned max_level() = 0;
    virtual Strategy strategy() = 0;
    virtual std::unordered_map<std::string, std::string>* next_level_ups() = 0;

    virtual ITower& set_strategy(Strategy new_strategy) = 0;
    virtual ITower& set_rapidity(double new_rapidity) = 0;
protected:
    virtual bool strategy_check(const std::shared_ptr<Entity>& checked, const std::shared_ptr<Entity>& target) =  0;
};

} // namespace WVM