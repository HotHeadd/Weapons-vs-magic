#pragma once

#include "effect.hpp"
#include "i_enemy.hpp"
#include "effected.hpp"

namespace WVM
{

class Slowdown : public Effect {
public:
    explicit Slowdown(std::shared_ptr<Effected> target);
    Slowdown(std::shared_ptr<Effected> target, unsigned strength, unsigned turns_to_last);
    void inflict() override;
    unsigned turns_to_last() const override;
    void set_duration(unsigned new_duration) override;
    unsigned strength() const override;
    void set_strength(unsigned new_strength) override;
    void neutralize() override;

    std::string_view type() override;
    Slowdown& set_type(std::string_view new_type) override;
    void on_death() override;

    static constexpr double slow_coef=0.2;
private:
    std::string type_ = "";

    std::weak_ptr<IEnemy> target_;
    unsigned strength_;
    unsigned turns_to_last_;

    bool is_inflicted_ = false;
};

} // namespace W