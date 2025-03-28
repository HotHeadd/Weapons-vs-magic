#pragma once

#include "i_system.hpp"
#include "i_sys_manager.hpp"
#include <unordered_set>
#include "i_lair.hpp"

namespace WVM
{

class LairSystem : public ISystem{
public:
    explicit LairSystem(ISystemManager& manager) noexcept;
    void update() override;
    void refresh() override;

    bool is_empty() override;

    std::unordered_set<std::shared_ptr<ILair>>& get_lairs();
private:
    bool check_type(const Entity* ptr) override;
    void do_remove(std::shared_ptr<void> obj) override;
    void do_add(std::shared_ptr<void> obj) override;
    std::unordered_set<std::shared_ptr<ILair>> lairs_;
    ISystemManager& manager_;
};

} // namespace WVM
