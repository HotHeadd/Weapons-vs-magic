#pragma once

#include "i_system.hpp"
#include <unordered_set>
#include "i_enemy.hpp"
#include "i_sys_manager.hpp"

namespace WVM
{

class EnemySystem : public ISystem {
public:
    explicit EnemySystem(ISystemManager& manager) noexcept;
    void update() override;
    void refresh() override;
    std::unordered_set<std::shared_ptr<IEnemy>>& get_enemies();
    bool is_empty() override;
protected:
    bool check_type(const Entity* ptr) override;

    void do_remove(std::shared_ptr<void> obj) override;
    void do_add(std::shared_ptr<void> obj) override;
    std::unordered_set<std::shared_ptr<IEnemy>> enemies_;
    ISystemManager& manager_;
};

} // namespace WVM
