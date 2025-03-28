#pragma once

#include "system_manager.hpp"
#include "factory_manager.hpp"
#include <memory>
#include "i_lair.hpp"
#include "i_tower.hpp"
#include "i_trap.hpp"
#include "castle.hpp"
#include "layout.hpp"

#include <string_view>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace WVM
{

class Game{
public:
    const std::string level_name;

    Game(std::shared_ptr<Layout> layout, std::shared_ptr<Castle> castle, std::string_view init_level_name); // создать от конфинга

    void load_config(const std::string& lib_name); //тут подгрузка ВООБЩЕ ВСЕХ сущностей в фабрики

    void save(const std::string& save_name);
    void save_script(const std::string& script_name);
    static Game load(const std::string& save_name);
    static Game load_script(const std::string& script_name);


    void update(); // обновление всех систем
    void refresh(); // refresh всех систем
    unsigned current_wave() {return current_wave_;}

    std::shared_ptr<ILair> add_empty_lair(Coordinates position);
    std::shared_ptr<ILair> add_lair(Coordinates position, std::vector<std::unordered_map<std::string, LairNode>>);


    std::shared_ptr<ITower> add_tower(std::string tower_name, Coordinates position); // метод менюшки
    std::shared_ptr<ITrap> add_trap(std::string trap_name, Coordinates position); // метод менюшки
    std::unordered_map<std::string, std::unique_ptr<TowerNode>>& list_all_towers(); // для менюшки в графике
    std::unordered_map<std::string, std::unique_ptr<TrapNode>>& list_all_traps();
    Layout& layout();
    Castle& castle();

    bool wave_end();
    bool game_over();
    SystemManager& get_sys_manager() {return system_manager_;}

    FactoryManager& get_fact_manager() {return fact_manager_;}
private:
    json get_game_json();
    json save_lairs();
    json save_defence();
    json save_enemies();

    static Game load_game_json(json&);
    void load_lairs(json&);
    void load_defence(json&);
    void load_enemies(json&);

    SystemManager system_manager_;
    FactoryManager fact_manager_;
    std::string lib_name_;

    unsigned current_wave_=1;
};

} // namespace WVM
