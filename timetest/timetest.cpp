#include "game.hpp"
#include "layout.hpp"
#include <limits>
#include "time_creators.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

using namespace WVM;
namespace fs = std::filesystem;

int main(){
    bool file_output = true;
    std::ofstream file;
    if (file_output){
        if (!fs::exists("timetest_report")){
            fs::create_directories("timetest_report");
        }
        file.open("timetest_report/results.txt");
    }
    std::shared_ptr<Layout> layout = std::make_shared<Layout>(3, 1000);
    layout->at(1, 999).set_type(TileType::CASTLE);
    layout->fill_row(0, TileType::FIELD);
    layout->fill_row(2, TileType::FIELD);
    layout->calculate_paths();
    std::shared_ptr<Castle> castle = std::make_shared<Castle>(std::numeric_limits<hp_t>::max());
    Game game(layout, castle, "test time");
    game.get_fact_manager().get_enemy_factory().add_enemy("bob", bob_timetest);
    game.get_fact_manager().get_tower_factory().add_tower("magic", std::make_unique<TowerNode>(magic_tower_timetest, 1));
    game.get_fact_manager().get_effect_factory().add_effect("poison", poisoning_timetest);
    game.get_fact_manager().get_effect_factory().add_effect("slow", slowdown_timetest);

    std::vector<std::unordered_map<std::string, LairNode>> instrs;
    std::unordered_map<std::string, LairNode> wave;
    wave.emplace("bob",  LairNode{std::numeric_limits<amount_t>::max(), 0});
    instrs.push_back(wave);
    for (int i=0;i<20; i++){
        game.add_lair({1, i}, instrs);
    }

    for (int i=0; i<500; i++){
        game.add_tower("magic", {0, i});
        game.add_tower("magic", {2, 2*i});
    }
    for (int i=0; i<130; i++){
        game.update();
    }
    std::cout << "Finished setup updates\n";
    for (int updates=10; updates<101; updates+=10){
        auto start = std::chrono::high_resolution_clock::now();
        for (int i=0; i<updates; i++){
            game.update();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        if (file_output){
            file << updates <<  " " << duration.count() << std::endl;
        }
    }
}