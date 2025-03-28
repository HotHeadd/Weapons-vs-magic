#include "tower.hpp"

namespace WVM
{

Tower::Tower(ISystemManager& manager,
    hp_t max_hp, 
    Coordinates position, 
    unsigned cost, 
    double vision_radius, 
    hp_t damage, 
    double rapidity, 
    std::vector<std::unordered_map<std::string, std::string>>& table): 
        manager_(manager), cost_(cost), vision_radius_(vision_radius),
        damage_(damage), rapidity_(rapidity),
        levelup_table_(table) {
    max_hp_ = max_hp;
    hp_ = max_hp;
    position_ = position;
    max_level_ = table.size()+1;
}

void Tower::reset_cooldown(){
    current_shot_cooldown_ = required_shot_points_;
}

void Tower::update(){
    current_shot_cooldown_ += rapidity_;
    if (current_shot_cooldown_ >= required_shot_points_){
        std::vector<std::shared_ptr<Entity>> targets;
        provide_targets(targets);
        for (auto& target : targets){
            affect_target(target);
        }
        if (targets.empty()){
            current_shot_cooldown_ += required_shot_points_ - rapidity_;
        }
        current_shot_cooldown_ -= required_shot_points_;
    }
}

bool Tower::strategy_check(const std::shared_ptr<Entity>& checked, const std::shared_ptr<Entity>& target){
    if (strategy_ == Strategy::CLOSEST_TO_CASTLE){
        Layout& layout = manager_.get_layout();
        return layout(checked->position()).steps_to_castle() < layout(target->position()).steps_to_castle();
    }
    if (strategy_ == Strategy::FARTHEST_FROM_CASTLE){
        Layout& layout = manager_.get_layout();
        return layout(checked->position()).steps_to_castle() > layout(target->position()).steps_to_castle();
    }
    if (strategy_ == Strategy::WEAKEST){
        IEnemy& checked_d = dynamic_cast<IEnemy&>(*checked);
        IEnemy& target_d = dynamic_cast<IEnemy&>(*target);
        return checked_d.hp() < target_d.hp();
        
    }
    if (strategy_ == Strategy::HEALTHIEST){
        IEnemy& checked_d = dynamic_cast<IEnemy&>(*checked);
        IEnemy& target_d = dynamic_cast<IEnemy&>(*target);
        return checked_d.hp() > target_d.hp();
    }
    if (strategy_ == Strategy::FASTEST){
        IEnemy& checked_d = dynamic_cast<IEnemy&>(*checked);
        IEnemy& target_d = dynamic_cast<IEnemy&>(*target);
        return checked_d.speed() > target_d.speed();
    }
    return false;
}

void Tower::provide_targets(std::vector<std::shared_ptr<Entity>>& targets){
    std::unordered_set<std::shared_ptr<IEnemy>>& enemies = manager_.get_enemies();
    for (auto& enemy : enemies){
        if (distance(*enemy, *this) > vision_radius_){
            continue;
        }
        if (targets.empty()){
            targets.push_back(enemy);
        }
        else{
            if (strategy_check(enemy, targets[0])){
                targets[0] = enemy;
            }

        }
    } 
}

void Tower::affect_target(std::shared_ptr<Entity> target){
    std::shared_ptr<IEnemy> e_target = std::static_pointer_cast<IEnemy>(target);
    std::lock_guard<std::mutex> lock_enemy(e_target->mutex());
    e_target->take_damage(damage_);
}

std::optional<unsigned> Tower::levelup_cost(){
    if (level_ == max_level_){
        return std::nullopt;
    }
    return std::stoi(levelup_table_[level_-1]["levelup_cost"]);
}

void Tower::level_up(){
    std::unordered_map<std::string, std::string>& instructions = levelup_table_[level_-1];
    if (instructions.contains("damage_up")){
        damage_ += std::stoi(instructions["damage_up"]);
    }
    if (instructions.contains("vision_up")){
        vision_radius_ +=  std::stoi(instructions["vision_up"]);
    }
    if (instructions.contains("cost_up")){
        cost_ += std::stoi(instructions["cost_up"]);
    }
    if (instructions.contains("rapidity_up")){
        rapidity_ += std::stoi(instructions["rapidity_up"]);
    }
    if (instructions.contains("max_hp_up")){
        max_hp_ += std::stoi(instructions["max_hp_up"]);
        hp_ = max_hp_;
    }
    ++level_;
}

void Tower::take_damage(hp_t amount){
    hp_ -= amount*damage_multiplier_;
}

void Tower::on_death() {}

void Tower::sell(){
    unsigned sell_cost = cost_/2;
    manager_.get_castle().increase_gold(sell_cost);
    hp_ = -10000;
}

unsigned Tower::cost(){
    return cost_;
}
Strategy Tower::strategy(){
    return strategy_;
}
double Tower::rapidity(){
    return rapidity_;
}
double Tower::vision_radius(){
    return vision_radius_;
}
hp_t Tower::shot_damage(){
    return damage_;
}

unsigned Tower::max_level(){
    return max_level_;
}

std::unordered_map<std::string, std::string>* Tower::next_level_ups(){
    if (level_ != max_level_){
        return &(levelup_table_[level_-1]);
    }
    return nullptr;
}

Tower& Tower::set_rapidity(double new_rapidity){
    rapidity_ = new_rapidity;
    return *this;
}

Tower& Tower::set_strategy(Strategy new_strategy){
    strategy_ = new_strategy;
    return *this;
}

Tower& Tower::set_vision(double new_vision){
    vision_radius_ = new_vision;
    return *this;
}

Tower& Tower::set_shot_damage(hp_t new_damage){
    damage_ = new_damage;
    return *this;
}

bool Tower::is_dead(){
    return hp_ <= 0;
}

std::string_view Tower::type(){
    return type_;
}

Tower& Tower::set_type(std::string_view new_type){
    type_ = new_type;
    return *this;
}

} // namespace WVM
