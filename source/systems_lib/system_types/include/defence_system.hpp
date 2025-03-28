#pragma once

#include "i_system.hpp"
#include "i_sys_manager.hpp"
#include "i_defence.hpp"
#include <unordered_set>
#include <thread>

namespace WVM
{

class DefenceSystem: public ISystem {
public:
    explicit DefenceSystem(ISystemManager& manager) noexcept;
    void update() override;
    void refresh() override;

    std::unordered_set<std::shared_ptr<IDefence>>& get_defence();
    bool is_empty() override;
private:
    bool check_type(const Entity* ptr) override;
    
    void do_remove(std::shared_ptr<void> obj) override;
    void do_add(std::shared_ptr<void> obj) override;
    std::unordered_set<std::shared_ptr<IDefence>> defence_;
    ISystemManager& manager_;
};

} // namespace WVM
