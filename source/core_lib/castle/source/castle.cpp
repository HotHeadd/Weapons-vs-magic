#include "castle.hpp"

namespace WVM
{

Castle::Castle(hp_t max_hp) : gold_(0) {
    max_hp_ = max_hp;
    hp_ = max_hp;
}

void Castle::take_damage(hp_t amount){
    hp_ -= amount*damage_multiplier_;
}

void Castle::increase_gold(unsigned amount){
    gold_ += amount;
}

void Castle::decrease_gold(unsigned amount){
    if (enough(amount)){
        gold_ -= amount;
    }
    else{
        gold_ = 0;
    }
}

bool Castle::enough(unsigned required){
    return gold_ >= required;
}

unsigned Castle::gold(){
    return gold_;
}

bool Castle::is_alive(){
    return hp_ > 0;
}

json Castle::save(){
    json castle_save = json::object();
    castle_save["gold"] = gold_;
    castle_save["max_hp"] = max_hp_;
    castle_save["hp"] = hp_;
    return castle_save;
}

std::shared_ptr<Castle> Castle::load(json& save_json){
    hp_t max_hp =  save_json["max_hp"];
    hp_t hp =  save_json["hp"];
    unsigned gold = save_json["gold"];
    std::shared_ptr<Castle> castle = std::make_shared<Castle>(max_hp);
    castle->hp_ = hp;
    castle->increase_gold(gold);
    return castle;
}

} // namespace WVM
