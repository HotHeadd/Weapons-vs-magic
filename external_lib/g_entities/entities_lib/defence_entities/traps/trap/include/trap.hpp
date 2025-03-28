#pragma once

#include "i_trap.hpp"
#include "i_sys_manager.hpp"


namespace WVM
{

/// @brief Класс ловушки, реализует основной функционал интерфейса ITrap
class Trap : public ITrap, public Shooting{
public:
    /// @brief Конструктор ловушки.
    /// @param manager Ссылка на менеджер системы игры.
    /// @param position Координаты установки ловушки.
    /// @param cost Стоимость установки ловушки.
    /// @param vision_radius Радиус обзора ловушки.
    /// @param effect_radius Радиус воздействия ловушки.
    /// @param damage Урон, наносимый ловушкой.
    Trap(
        ISystemManager& manager,
        Coordinates position,
        unsigned cost,
        double vision_radius,
        double effect_radius,
        hp_t damage
    );
    /// @brief Продает ловушку, освобождая ресурсы и удаляя её из системы и возвращает часть стоимости замку.
    void sell() override;
    /// @brief Обновляет состояние ловушки, например, проверяет наличие целей в радиусе действия.
    void update() override;

    /// @brief Возвращает урон, наносимый ловушкой.
    /// @return Урон ловушки.
    hp_t shot_damage() override;

    /// @brief Возвращает радиус обзора ловушки.
    /// @return Радиус обзора.
    double vision_radius() override;

    /// @brief Проверяет, уничтожена ли ловушка.
    /// @return True, если ловушка уничтожена, иначе False.
    bool is_dead() override;

    /// @brief Возвращает стоимость установки ловушки.
    /// @return Стоимость ловушки.
    unsigned cost() override;

    /// @brief Возвращает радиус воздействия ловушки.
    /// @return Радиус воздействия.
    double effect_radius() {return effect_radius_;}

    /// @brief Устанавливает новый радиус обзора ловушки.
    /// @param new_vision Новый радиус обзора.
    /// @return Ссылка на текущую ловушку.
    Trap& set_vision(double new_vision) override;

    /// @brief Устанавливает новый урон ловушки.
    /// @param new_damage Новый урон.
    /// @return Ссылка на текущую ловушку.
    Trap& set_shot_damage(hp_t new_damage) override;

    /// @brief Сбрасывает перезарядку ловушки, делая её готовой к следующей атаке.
    void reset_cooldown() override;
    /// @brief Вызывается при уничтожении ловушки, выполняет завершающие действия.
    void on_death() override;

    /// @brief Возвращает тип ловушки в виде строки.
    /// @return Тип ловушки.
    std::string_view type() override;

    /// @brief Устанавливает тип ловушки.
    /// @param new_type Новый тип ловушки.
    /// @return Ссылка на текущую ловушку.
    Trap& set_type(std::string_view new_type) override;
protected:
    /// @brief Определяет цели для ловушки в радиусе её действия.
    /// @param targets Вектор целей для атаки.
    void provide_targets(std::vector<std::shared_ptr<Entity>>& targets) override;
    /// @brief Применяет воздействие ловушки на указанную цель (в данной реализации нанесение урона ловушки).
    /// @param target Цель воздействия.
    void affect_target(std::shared_ptr<Entity> target) override;
    unsigned cost_; ///< Стоимость ловушки.
    double vision_radius_; ///< Радиус обзора ловушки.
    double effect_radius_; ///< Радиус воздействия ловушки.
    hp_t damage_; ///< Урон ловушки.

    std::string type_; ///< Тип ловушки.
    ISystemManager& manager_; ///< Ссылка на менеджер системы.
    bool is_dead_=false; ///< Флаг состояния уничтожения ловушки.
};

} // namespace WVM
