#pragma once
#include <memory>
#include "entity.hpp"
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"

#include"effected.hpp"

using namespace WVM;


std::shared_ptr<Effect> create_poisoning(std::shared_ptr<Effected> target);
std::shared_ptr<Effect> create_weakening(std::shared_ptr<Effected> target);
std::shared_ptr<Effect> create_slowdown(std::shared_ptr<Effected> target);

std::shared_ptr<Entity> create_bob(ISystemManager& manager, IFactoryManager& f_manager);
std::shared_ptr<Entity> create_tank(ISystemManager& manager, IFactoryManager& f_manager);

std::shared_ptr<Entity> create_simple_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode&);
std::shared_ptr<Entity> create_magic_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode&);

std::shared_ptr<Entity> create_simple_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node);
std::shared_ptr<Entity> create_magic_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node);