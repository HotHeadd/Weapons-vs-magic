#pragma once

#include "i_tower_factory.hpp"
#include <unordered_map>


namespace WVM
{

class TowerFactory : public ITowerFactory{
public:
    explicit TowerFactory(ISystemManager& manager, IFactoryManager& fact_manager) : manager_(manager), fact_manager_(fact_manager) {}
    std::shared_ptr<Entity> create_from_json() override;
    std::shared_ptr<Entity> create(const std::string& name) override;

    void add_tower(std::string name, std::unique_ptr<TowerNode>) override;

    bool can_create(const std::string& name) override;
    unsigned get_cost(const std::string& name) override;

    std::unordered_map<std::string, std::unique_ptr<TowerNode>>& creators();
private:
    ISystemManager& manager_;
    IFactoryManager& fact_manager_;
    std::unordered_map<std::string, std::unique_ptr<TowerNode>> creators_;
};

} // namespace WVM