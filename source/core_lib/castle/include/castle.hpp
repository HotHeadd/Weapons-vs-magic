#pragma once

#include <string>
#include "damagable.hpp"
#include "persistable.hpp"

namespace WVM
{

class Castle : public Damagable{
public:
    Castle(hp_t max_hp);
    void increase_gold(unsigned amount);
    void decrease_gold(unsigned amount);
    bool enough(unsigned required);
    void take_damage(hp_t amount) override;

    unsigned gold();
    bool is_alive();

    json save();
    static std::shared_ptr<Castle> load(json&);
private:
    unsigned gold_;
};


} // namespace WVM
