#pragma once

#include "trap.hpp"
#include "magic.hpp"
#include "i_sys_manager.hpp"

namespace WVM
{

/// @brief Класс магической ловушки в игре Tower Defense, расширяет функциональность Trap и Magic (при affect_target накладывает эффекты на врага).
class MagicTrap : public Trap, public Magic {
public:
    /// @brief Конструктор магической ловушки.
    /// @param manager Ссылка на менеджер системы игры.
    /// @param factory Фабрика эффектов для создания магических воздействий.
    /// @param position Координаты установки ловушки.
    /// @param cost Стоимость установки ловушки.
    /// @param vision_radius Радиус обзора ловушки.
    /// @param effect_radius Радиус воздействия ловушки.
    /// @param damage Урон, наносимый ловушкой.
    /// @param magic_effects Словарь магических эффектов, применяемых ловушкой.
    MagicTrap(
        ISystemManager& manager,
        IEffectFactory& factory,
        Coordinates position,
        unsigned cost,
        double vision_radius,
        double effect_radius,
        hp_t damage,
        std::unordered_map<std::string, MagicNode>& magic_effects
    );
protected:
    /// @brief Применяет воздействие магической ловушки на указанную цель (наносит урон и накладывает эффекты).
    /// @param target Цель воздействия.
    void affect_target(std::shared_ptr<Entity> target) override;
};

} // namespace WVM
