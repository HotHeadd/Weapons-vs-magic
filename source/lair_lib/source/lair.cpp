#include "lair.hpp"
#include <array>
#include <set>
#include <limits>

namespace WVM
{

void Lair::choose_spawn_point_(const Coordinates& check_pos){
    Layout& layout = manager_.get_layout();
    Coordinates new_point = {-1, -1};
    unsigned current_dist = std::numeric_limits<unsigned>::max();
    std::array<Coordinates, 8> directions = {Tile::UP, Tile::DOWN, Tile::LEFT, Tile::RIGHT, Tile::U_LEFT, Tile::U_RIGHT, Tile::D_LEFT, Tile::D_RIGHT};
    std::set<Coordinates> diag_directions = {Tile::D_LEFT, Tile::D_RIGHT, Tile::U_LEFT, Tile::U_RIGHT};
    for (auto& diff : directions){
        Coordinates current_coords = check_pos+diff;
        if (!layout.contains(current_coords)){
            continue;
        }
        Tile& current_tile = layout(current_coords);
        if (current_tile.type() != TileType::ROAD){
            continue;
        }
        if (current_tile.steps_to_castle() < current_dist){
            new_point = current_coords;
            current_dist = current_tile.steps_to_castle();
        }
        if (current_tile.steps_to_castle() == current_dist and
        diag_directions.contains(layout(new_point).direction())){
            new_point = current_coords;
        }
    }
    if (new_point.x == -1){
        throw std::logic_error("Not a suitable location for lair");
    }
    spawn_point_ = new_point;
}

Lair::Lair(ISystemManager& manager, IEnemyFactory& factory, Coordinates position) : 
            manager_(manager), factory_(factory) {
    position_ = position;
    choose_spawn_point_(position);
    current_wave_ = 1;
}

Lair::Lair(ISystemManager& manager, IEnemyFactory& factory, Coordinates position,
         std::vector<std::unordered_map<std::string, LairNode>> instructions) : 
            manager_(manager), factory_(factory), wave_spawn_instrucitons_(instructions) {
    position_ = position;
    choose_spawn_point_(position);
    current_wave_ = 1;
    load_wave_instruction();
}

void Lair::move(Coordinates new_pos){
    Entity::move(new_pos);
    choose_spawn_point_(new_pos);
}

void Lair::update(){
    for (auto& lair_pair : current_wave_enemies_){
        auto& node = lair_pair.second;
        if (node.current_cooldown == node.cooldown and node.current_amount > 0){
            std::string name = lair_pair.first;

            std::shared_ptr<IEnemy> new_enemy = std::static_pointer_cast<IEnemy>(factory_.create(name));
            new_enemy->move(spawn_point_);
            manager_.get_system(SystemTag::ENEMY).add(new_enemy);
            manager_.get_system(SystemTag::EFFECT).add(new_enemy);
            
            node.current_amount -= 1;
            node.current_cooldown = 0;
        }
        else{
            node.current_cooldown += 1;
        }
    }
}

void Lair::on_death() {}

bool Lair::no_enemies_left(){
    for (auto& lair_pair : current_wave_enemies_){
        if (lair_pair.second.current_amount > 0){
            return false;
        } 
    }
    return true;
}

void Lair::wave_up(){
    current_wave_ += 1;
    load_wave_instruction();
}

void Lair::load_wave_instruction(){
    if (current_wave_-1 >= wave_spawn_instrucitons_.size()){
        current_wave_enemies_ = wave_spawn_instrucitons_.back();
    }
    else{
        current_wave_enemies_ = wave_spawn_instrucitons_[current_wave_-1];
    }
}

Coordinates Lair::spawn_point(){
    return spawn_point_;
}

void Lair::add_spawn_instructions(std::vector<std::unordered_map<std::string, LairNode>> new_instructions){
    if (new_instructions.empty()){
        throw std::logic_error("Add spawn instruction: Empty spawn instructions for lair");
    }
    wave_spawn_instrucitons_ = std::move(new_instructions);
    load_wave_instruction();
}

std::vector<std::unordered_map<std::string, LairNode>>& Lair::spawn_instructions(){
    return wave_spawn_instrucitons_;
}

std::string_view Lair::type(){
    throw std::logic_error("Lair has no type");
}
Lair& Lair::set_type(std::string_view new_type){
    throw std::logic_error("Lair has no type");
}

json Lair::save(){
    json lair_json = json::object();
    lair_json["x"] = position_.x;
    lair_json["y"] = position_.y;
    lair_json["current_wave_num"] = current_wave_;
    lair_json["current_wave_instructions"] = save_enemies_json(current_wave_enemies_);
    lair_json["wave_instructions"] = save_wave_instructions_json();
    return lair_json;
}

json Lair::save_enemies_json(std::unordered_map<std::string, LairNode>& instructions){
    json instr_json = json::array();
    for (auto& enemy_instr : instructions){
        json enemy_instr_json = json::object();
        json node_json = json::object();
        node_json["amount"] = enemy_instr.second.amount;
        node_json["cooldown"] = enemy_instr.second.cooldown;
        node_json["current_cooldown"] = enemy_instr.second.current_cooldown;
        node_json["current_amount"] = enemy_instr.second.current_amount;
        enemy_instr_json[enemy_instr.first] = node_json;
        instr_json.push_back(enemy_instr_json);
    }
    return instr_json;
}

json Lair::save_wave_instructions_json(){
    json instr_json = json::array();
    for (auto& current_instr : wave_spawn_instrucitons_){
        instr_json.push_back(save_enemies_json(current_instr));
    }
    return instr_json;
}

void Lair::load(json& lair_json){
    std::vector<std::unordered_map<std::string, LairNode>> wave_instrucitons;
    for (auto& instruciton : lair_json["wave_instructions"]){
        std::unordered_map<std::string, LairNode> new_instruction;
        for (auto& enemy_elem : lair_json["current_wave_instructions"]){
            std::string name = enemy_elem.begin().key();
            json enemy_instr = enemy_elem.begin().value();
            amount_t amount = enemy_instr["amount"];
            cooldown_t cooldown = enemy_instr["cooldown"];
            amount_t current_amount = enemy_instr["current_amount"];
            cooldown_t current_cooldown = enemy_instr["current_cooldown"];
            LairNode node(amount, cooldown);
            node.current_amount = current_amount;
            node.current_cooldown = current_cooldown;
            new_instruction.emplace(name, node);
        }
        wave_instrucitons.push_back(std::move(new_instruction));
    }
    add_spawn_instructions(std::move(wave_instrucitons));
    current_wave_ = lair_json["current_wave_num"];
    for (auto& enemy_elem : lair_json["current_wave_instructions"]){
        std::string name = enemy_elem.begin().key();
        json enemy_instr = enemy_elem.begin().value();
        amount_t amount = enemy_instr["amount"];
        cooldown_t cooldown = enemy_instr["cooldown"];
        amount_t current_amount = enemy_instr["current_amount"];
        cooldown_t current_cooldown = enemy_instr["current_cooldown"];
        LairNode node(amount, cooldown);
        node.current_amount = current_amount;
        node.current_cooldown = current_cooldown;
        current_wave_enemies_.emplace(name, node);
    }
}

} // namespace WVM
