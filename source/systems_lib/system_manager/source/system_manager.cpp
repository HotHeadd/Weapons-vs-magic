#include "system_manager.hpp"
#include "enemy_system.hpp"
#include "defence_system.hpp"
#include "lair_system.hpp"
#include "effect_system.hpp"

namespace WVM
{

SystemManager::SystemManager(std::shared_ptr<Layout> layout, std::shared_ptr<Castle> castle) : 
                layout_(layout), castle_(castle) {
    systems_.emplace(SystemTag::EFFECT, std::make_shared<EffectSystem>(*this));
    systems_.emplace(SystemTag::DEFENCE, std::make_shared<DefenceSystem>(*this));
    systems_.emplace(SystemTag::ENEMY, std::make_shared<EnemySystem>(*this));
    systems_.emplace(SystemTag::LAIR, std::make_shared<LairSystem>(*this));
}

Layout& SystemManager::get_layout(){
    return *layout_;
}

Castle& SystemManager::get_castle(){
    return *castle_;
}

ISystem& SystemManager::get_system(SystemTag tag) {
    return *(systems_[tag]);
}

SystemManager::ManagerIterator
SystemManager::begin(){
    return systems_.begin();
}

SystemManager::ManagerIterator
SystemManager::end(){
    return systems_.end();
}

std::unordered_set<std::shared_ptr<IEnemy>>& SystemManager::get_enemies(){
    ISystem& return_system = get_system(SystemTag::ENEMY);
    EnemySystem& e_system = dynamic_cast<EnemySystem&>(return_system);
    return e_system.get_enemies();
}
std::unordered_set<std::shared_ptr<IDefence>>& SystemManager::get_defence(){
    ISystem& return_system = get_system(SystemTag::DEFENCE);
    DefenceSystem& d_system = dynamic_cast<DefenceSystem&>(return_system);
    return d_system.get_defence();
}

std::unordered_set<std::shared_ptr<ILair>>& SystemManager::get_lairs(){
    ISystem& return_system = get_system(SystemTag::LAIR);
    LairSystem& l_system = dynamic_cast<LairSystem&>(return_system);
    return l_system.get_lairs();
}

} // namespace WVM
