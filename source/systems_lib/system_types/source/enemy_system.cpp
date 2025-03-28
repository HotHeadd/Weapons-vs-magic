#include "enemy_system.hpp"

namespace WVM
{

EnemySystem::EnemySystem(ISystemManager& manager) noexcept : manager_(manager) {}

void EnemySystem::update(){
    Layout& layout = manager_.get_layout();
    for (auto iter = enemies_.begin(); iter != enemies_.end();){
        auto enemy = *iter;
        ++iter;
        if (enemy->hp() <= 0){
            remove(enemy);
            enemy->on_death();
        }
        else{
            enemy->update();
            if (layout(enemy->position()).type() == TileType::CASTLE){
                manager_.get_castle().take_damage(enemy->damage());
                remove(enemy);
            }
        }
    }
}

void EnemySystem::refresh(){}

bool EnemySystem::check_type(const Entity* ptr){
    return dynamic_cast<const IEnemy*>(ptr) != nullptr;
}

void EnemySystem::do_remove(std::shared_ptr<void> obj){
    std::shared_ptr<IEnemy> enemy = std::static_pointer_cast<IEnemy>(obj);
    if (!enemies_.contains(enemy)){
        throw std::runtime_error("Enemy not in enemies");
    }
    enemies_.erase(enemy);
}

void EnemySystem::do_add(std::shared_ptr<void> obj){
    std::shared_ptr<IEnemy> enemy = std::static_pointer_cast<IEnemy>(obj);
    if (enemies_.contains(enemy)){
        throw std::runtime_error("Enemy already in enemies");
    }
    enemies_.insert(enemy);
}

std::unordered_set<std::shared_ptr<IEnemy>>& EnemySystem::get_enemies(){
    return enemies_;
}

bool EnemySystem::is_empty(){
    return enemies_.empty();
}

} // namespace WVM
