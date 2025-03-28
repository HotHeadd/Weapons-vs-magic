#pragma once

#include "../traits/effect.hpp"
#include "effected.hpp"
#include <memory>
#include <functional>

namespace WVM
{

class IEffectFactory {
public:
    virtual std::shared_ptr<Effect> create_from_json() = 0;
    virtual std::shared_ptr<Effect> create(const std::string& name, std::shared_ptr<Effected> target) = 0;

    virtual void add_effect(std::string name, std::function<std::shared_ptr<Effect>(std::shared_ptr<Effected>)> creator) = 0;
    virtual bool can_create(const std::string& name) = 0;
private:
};

} // namespace WVM
