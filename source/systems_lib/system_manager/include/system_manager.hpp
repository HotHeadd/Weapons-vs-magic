#pragma once

#include "i_system.hpp"
#include "i_sys_manager.hpp"
#include "i_lair.hpp"
#include "layout.hpp"
#include "castle.hpp"
#include <map>
#include <memory>

namespace WVM
{

class SystemManager : public ISystemManager{
public:
    using ISystemManager::ManagerIterator;
    SystemManager(std::shared_ptr<Layout> layout, std::shared_ptr<Castle> castle); //создает все системы

    ISystem& get_system(SystemTag tag) override;
    Layout& get_layout() override;
    Castle& get_castle() override;

    ManagerIterator begin() override;
    ManagerIterator end() override;

    std::unordered_set<std::shared_ptr<IDefence>>& get_defence() override;
    std::unordered_set<std::shared_ptr<IEnemy>>& get_enemies() override;
    std::unordered_set<std::shared_ptr<ILair>>& get_lairs();
private:
    std::shared_ptr<Layout> layout_;
    std::shared_ptr<Castle> castle_;
    std::map<SystemTag, std::shared_ptr<ISystem>> systems_;
};

}