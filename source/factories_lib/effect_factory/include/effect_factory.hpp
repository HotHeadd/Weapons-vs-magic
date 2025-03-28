#pragma once

#include "i_effect_factory.hpp"
#include <memory>
#include <unordered_map>
#include <functional>


namespace WVM
{

class EffectFactory : public IEffectFactory{
public:
    std::shared_ptr<Effect> create_from_json() override;
    std::shared_ptr<Effect> create(const std::string& name, std::shared_ptr<Effected> target) override;

    void add_effect(std::string name, std::function<std::shared_ptr<Effect>(std::shared_ptr<Effected>)> creator) override;

    bool can_create(const std::string& name) override;
private:
    std::unordered_map<std::string, std::function<std::shared_ptr<Effect>(std::shared_ptr<Effected>)>> creators_;
};

} // namespace WVM
