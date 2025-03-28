#pragma once

#include "i_lair.hpp"
#include "i_sys_manager.hpp"
#include "i_enemy_factory.hpp"
#include <unordered_map>
#include <vector>

namespace WVM
{

class Lair : public ILair{
public:
    Lair(ISystemManager& manager, IEnemyFactory& factory, Coordinates position);
    Lair(ISystemManager& manager, IEnemyFactory& factory, Coordinates position,
         std::vector<std::unordered_map<std::string, LairNode>> instructions);
    void move(Coordinates new_pos) override;

    void update() override;
    void on_death() override;

    bool no_enemies_left() override;
    void wave_up() override;

    Coordinates spawn_point();
    void add_spawn_instructions(std::vector<std::unordered_map<std::string, LairNode>>) override;
    std::vector<std::unordered_map<std::string, LairNode>>& spawn_instructions() override;

    std::string_view type() override;
    Lair& set_type(std::string_view new_type) override;

    json save() override;
    void load(json&) override;
private:
    json save_enemies_json(std::unordered_map<std::string, LairNode>&);
    json save_wave_instructions_json();

    void choose_spawn_point_(const Coordinates& pos);
    void load_wave_instruction();
    ISystemManager& manager_;
    IEnemyFactory& factory_;

    unsigned current_wave_;
    Coordinates spawn_point_;
    std::unordered_map<std::string, LairNode> current_wave_enemies_;
    std::vector<std::unordered_map<std::string, LairNode>> wave_spawn_instrucitons_;
};

} // namespace WVM
