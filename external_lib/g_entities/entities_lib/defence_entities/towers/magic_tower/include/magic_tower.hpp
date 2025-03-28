#pragma once

#include "tower.hpp"
#include "magic.hpp"
#include "effect.hpp"
#include "i_sys_manager.hpp"

namespace WVM
{

/// @brief Класс магической башни, наследующий функциональность стандартной башни и добавляющий магические эффекты при выстреле.
class MagicTower : public Tower, public Magic {
public:
    /// @brief Конструктор магической башни.
    /// @param manager Ссылка на менеджер системы игры.
    /// @param factory Ссылка на фабрику эффектов.
    /// @param hp Очки здоровья башни.
    /// @param position Координаты расположения башни.
    /// @param cost Стоимость постройки башни.
    /// @param vision_radius Радиус обзора башни.
    /// @param damage Урон, наносимый башней за выстрел.
    /// @param rapidity Скорострельность башни.
    /// @param table Таблица улучшений башни.
    /// @param magic_effects Набор магических эффектов башни.
    MagicTower(ISystemManager& manager,
        IEffectFactory& factory,
        hp_t hp, 
        Coordinates position, 
        unsigned cost, 
        double vision_radius, 
        hp_t damage, 
        double rapidity, 
        std::vector<std::unordered_map<std::string, std::string>>& table,
        std::unordered_map<std::string, MagicNode>& magic_effects);

    /// @brief Улучшает уровень магической башни, вызывает Tower::level_up, а также обрабатывает улучшение накладываемых эффектов
    void level_up() override;
protected:
    /// @brief Применяет магический эффект к указанной цели и наносит ей урон.
    /// @param target Цель, на которую воздействует магическая башня.
    void affect_target(std::shared_ptr<Entity> target) override;
};

} // namespace WVM
