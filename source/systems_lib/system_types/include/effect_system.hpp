#pragma once

#include "effected.hpp"
#include "i_system.hpp"
#include "i_sys_manager.hpp"

#include <memory>
#include <list>

namespace WVM
{

class EffectSystem: public ISystem{
public:
    explicit EffectSystem(ISystemManager& manager) noexcept;
    void update() override;
    void refresh() override;

    bool is_empty() override;
private:
    bool check_type(const Entity* ptr) override;

    void do_remove(std::shared_ptr<void> obj) override;
    void do_add(std::shared_ptr<void> obj) override;
    
    std::list<std::weak_ptr<Effected>> targets_;
    ISystemManager& manager_;
};

} // namespace WVM