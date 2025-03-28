#pragma once
#include <memory>
#include "entity.hpp"
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"

using namespace WVM;

std::shared_ptr<Entity> create_simple_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node);
std::shared_ptr<Entity> create_magic_trap(ISystemManager& manager, IFactoryManager& f_manager, TrapNode& node);