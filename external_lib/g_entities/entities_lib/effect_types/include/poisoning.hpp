#pragma once

#include "effect.hpp"
#include "damagable.hpp"
#include <memory>
#include "effected.hpp"

namespace WVM
{

class Poisoning : public Effect {
public:
    explicit Poisoning(std::shared_ptr<Effected> target);
    Poisoning(std::shared_ptr<Effected> target, unsigned strength, unsigned ticks);

    void inflict() override;
    void neutralize() override;

    unsigned turns_to_last() const override;
    void set_duration(unsigned new_duration) override;
    unsigned strength() const override;
    void set_strength(unsigned new_strength) override;

    std::string_view type() override;
    Poisoning& set_type(std::string_view new_type) override;
    void on_death() override;

    static constexpr unsigned hp_per_tick = 2;
    static constexpr unsigned tick_cooldown = 15;
private:
    std::string type_ = "";

    std::weak_ptr<Damagable> target_;
    unsigned strength_;
    unsigned ticks_;
    unsigned current_cooldown_;
};

} // namespace WVM
