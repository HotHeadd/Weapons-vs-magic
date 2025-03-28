#pragma once
#include <memory>
#include "entity.hpp"
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"

using namespace WVM;

std::shared_ptr<Entity> create_simple_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode&);
std::shared_ptr<Entity> create_magic_tower(ISystemManager& manager, IFactoryManager& f_manager, TowerNode&);