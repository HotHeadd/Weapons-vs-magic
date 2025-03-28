#include "magic_tower.hpp"
#include <charconv>
#include <string_view>

namespace WVM
{
    
MagicTower::MagicTower(ISystemManager& manager,
        IEffectFactory& factory,
        hp_t hp, 
        Coordinates position, 
        unsigned cost, 
        double vision_radius, 
        hp_t damage, 
        double rapidity,
        std::vector<std::unordered_map<std::string, std::string>>& table,
        std::unordered_map<std::string, MagicNode>& magic_effects) : 
            Magic(factory),
            Tower(manager, hp, position, cost, vision_radius, damage, rapidity, table){
    magic_effects_ = magic_effects;
}

void MagicTower::level_up(){
    std::unordered_map<std::string, std::string>& instructions = levelup_table_[level_-1];
    try{
        if (instructions.contains("add_magic_effect")){
            std::string_view to_parse = instructions["add_magic_effect"];
            size_t first_sep = to_parse.find(' '), second_sep = to_parse.find(' ', first_sep+1);

            std::string_view effect_name = to_parse.substr(0, first_sep), 
                             strength_view = to_parse.substr(first_sep+1, second_sep-first_sep),
                             duration_view = to_parse.substr(second_sep+1);

            unsigned effect_strength, effect_duration;
            std::from_chars(strength_view.begin(), strength_view.end(), effect_strength);
            std::from_chars(duration_view.begin(), duration_view.end(), effect_duration);

            magic_effects_[std::string(effect_name)] = MagicNode{effect_strength, effect_duration};
        }
        if (instructions.contains("up_effect_strength")){
            std::string_view to_parse = instructions["up_effect_strength"];
            size_t sep = to_parse.find(' ');

            std::string_view effect_name = to_parse.substr(0, sep), 
                             strength_view = to_parse.substr(sep+1);
            
            
            unsigned strength_bonus;
            std::from_chars(strength_view.begin(), strength_view.end(), strength_bonus);

            MagicNode& node = magic_effects_[std::string(effect_name)];
            node.e_strength += strength_bonus;
        }
        if (instructions.contains("up_effect_duration")){
            std::string_view to_parse = instructions["up_effect_duration"];
            size_t sep = to_parse.find(' ');

            std::string_view effect_name = to_parse.substr(0, sep), 
                             duration_view = to_parse.substr(sep+1);

            unsigned duration_bonus;
            std::from_chars(duration_view.begin(), duration_view.end(), duration_bonus);

            MagicNode& node = magic_effects_[std::string(effect_name)];
            node.e_duration += duration_bonus;
        }
        Tower::level_up();
    }
    catch (std::exception& e){
        throw std::logic_error("Corrupted levelup tower instruction file");
    }

}

void MagicTower::affect_target(std::shared_ptr<Entity> target){
    std::shared_ptr<IEnemy> e_target = std::static_pointer_cast<IEnemy>(target);
    std::lock_guard<std::mutex> lock_enemy(e_target->mutex());
    cast_spell(e_target);
    e_target->take_damage(damage_);
}

} // namespace WVM
