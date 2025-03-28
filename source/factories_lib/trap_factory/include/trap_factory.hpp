#pragma once

#include "i_trap_factory.hpp"
#include "i_factory_manager.hpp"
#include <string>
#include <unordered_map>

namespace WVM
{

class TrapFactory : public ITrapFactory{
public:
    explicit TrapFactory(ISystemManager& manager, IFactoryManager& fact_manager) : manager_(manager), fact_manager_(fact_manager) {}
    std::shared_ptr<Entity> create_from_json() override;
    std::shared_ptr<Entity> create(const std::string& name) override;

    void add_trap(std::string name, std::unique_ptr<TrapNode>) override;

    void levelup_trap(const std::string& name);

    unsigned get_cost(const std::string& name);
    unsigned get_levelup_cost(const std::string& name);
    unsigned get_level(const std::string& name);
    unsigned get_max_level(const std::string& name);

    bool can_create(const std::string& name) override;
    std::unordered_map<std::string, std::unique_ptr<TrapNode>>& creators();
private:
    ISystemManager& manager_;
    IFactoryManager& fact_manager_;
    std::unordered_map<std::string, std::unique_ptr<TrapNode>> creators_;
};

} // namespace WVM