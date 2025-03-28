#pragma once

#include "i_tower.hpp"
#include "shooting.hpp"
#include "i_sys_manager.hpp"
#include <vector>
#include <unordered_map>
#include <string>

namespace WVM
{
/// @brief Расширяемый класс башни, реализующий методы интерфейса башни (и интерфейса Shooting, так как башня стреляющая)
class Tower : public ITower, public Shooting{
public:
    /// @brief Конструктор башни.
    /// @param manager Ссылка на менеджер системы игры.
    /// @param hp Очки здоровья башни.
    /// @param position Координаты расположения башни.
    /// @param cost Стоимость постройки башни.
    /// @param vision_radius Радиус обзора башни.
    /// @param damage Урон, наносимый башней за выстрел.
    /// @param rapidity Скорострельность башни.
    /// @param table Таблица улучшений башни.
    Tower(ISystemManager& manager,
        hp_t hp, 
        Coordinates position, 
        unsigned cost, 
        double vision_radius, 
        hp_t damage, 
        double rapidity, 
        std::vector<std::unordered_map<std::string, std::string>>& table
    );
    /// @brief Улучшает уровень башни, увеличивая ее характеристики в соотвествии со сценарием повышения уровня.
    void level_up() override;
    /// @brief Продает башню, возвращая часть стоимости в замок.
    void sell() override;

    /// @brief Возвращает стоимость следующего улучшения башни.
    /// @return Стоимость следующего улучшения, если оно возможно.
    virtual std::optional<unsigned> levelup_cost();

    /// @brief Возвращает текущую стоимость башни.
    /// @return Стоимость башни.
    unsigned cost() override;

    /// @brief Возвращает текущую стратегию выбора врага башни.
    /// @return Текущая стратегия прицеливания.
    Strategy strategy() override;

    /// @brief Возвращает текущую скорострельность башни.
    /// @return Скорострельность башни.
    double rapidity() override;

    /// @brief Возвращает текущий радиус обзора башни.
    /// @return Радиус обзора.
    double vision_radius() override;

    /// @brief Возвращает урон от одного выстрела башни.
    /// @return Урон от выстрела.
    hp_t shot_damage() override;

    /// @brief Возвращает текущий уровень башни.
    /// @return Текущий уровень.
    unsigned level() override {return level_;}

    /// @brief Возвращает максимально возможный уровень башни.
    /// @return Максимальный уровень.
    unsigned max_level() override;

    /// @brief Возвращает описание возможных улучшений на следующем уровне.
    /// @return Указатель на таблицу улучшений следующего уровня.
    std::unordered_map<std::string, std::string>* next_level_ups() override;

    /// @brief Устанавливает новую стратегию прицеливания.
    /// @param new_strategy Новая стратегия.
    /// @return Ссылка на текущий объект башни.
    Tower& set_strategy(Strategy new_strategy) override;

    /// @brief Устанавливает новую скорострельность башни.
    /// @param new_rapidity Новая скорострельность.
    /// @return Ссылка на текущий объект башни.
    Tower& set_rapidity(double new_rapidity) override;

    /// @brief Устанавливает новый радиус обзора башни.
    /// @param new_vision Новый радиус обзора.
    /// @return Ссылка на текущий объект башни.
    Tower& set_vision(double new_vision) override;

    /// @brief Устанавливает новый урон от выстрела.
    /// @param new_damage Новый урон.
    /// @return Ссылка на текущий объект башни.
    Tower& set_shot_damage(hp_t new_damage) override;

    /// @brief Обновляет состояние башни (для этой башни -- увеличивает кулдаун выстрела, если набралось достаточное количество очков выстрела, то вызывает методы provide_targets и affect_target)
    void update() override;

    /// @brief Сбрасывает кулдаун на выстрел башни
    void reset_cooldown() override;

    /// @brief Наносит башне урон.
    /// @param amount Количество урона.
    void take_damage(hp_t amount) override;

    /// @brief Вызывается при уничтожении башни.
    void on_death() override;

    /// @brief Проверяет, уничтожена ли башня.
    /// @return true, если башня уничтожена, иначе false.
    bool is_dead() override;

    /// @brief Возвращает тип башни.
    /// @return Тип башни в виде строки.
    std::string_view type() override;

    /// @brief Устанавливает новый тип башни.
    /// @param new_type Новый тип башни.
    /// @return Ссылка на текущий объект башни.
    Tower& set_type(std::string_view new_type) override;
protected:
    /// @brief Проверяет, соответствует ли цель текущей стратегии.
    /// @param checked Проверяемая цель.
    /// @param target Текущая цель.
    /// @return true, если цель соответствует стратегии.
    bool strategy_check(const std::shared_ptr<Entity>& checked, const std::shared_ptr<Entity>& target) override;

    /// @brief Предоставляет список целей для башни (в данном случае одного подходящего врага) в соотвествии с выбранной стратегией.
    /// @param targets Вектор целей.
    void provide_targets(std::vector<std::shared_ptr<Entity>>& targets) override;

    /// @brief Осуществляет воздействие на указанную цель (в данном случае наносит ей урон башни).
    /// @param target Цель, на которую воздействует башня.
    void affect_target(std::shared_ptr<Entity> target) override;
    unsigned cost_; ///< Стоимость башни.
    double vision_radius_; ///< Радиус обзора башни.
    hp_t damage_; ///< Скорострельность башни.
    double rapidity_; ///< Скорострельность башни.
    Strategy strategy_=Strategy::CLOSEST_TO_CASTLE; ///< Текущая стратегия прицеливания.

    std::vector<std::unordered_map<std::string, std::string>> levelup_table_;  ///< Таблица улучшений башни.
    unsigned level_ = 1; ///< Текущий уровень башни.
    unsigned max_level_; ///< Максимальный уровень башни.

    ISystemManager& manager_; ///< Ссылка на менеджер системы игры.
    std::string type_ = ""; ///< Тип башни.

    static constexpr double required_shot_points_ = 1000; ///< Очки, требуемые для выстрела.
    double current_shot_cooldown_ = 1000; ///< Текущее состояние перезарядки выстрела.
};

} // namespace WVM
