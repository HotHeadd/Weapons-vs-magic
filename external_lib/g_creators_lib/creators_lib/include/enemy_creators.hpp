#pragma once
#include <memory>
#include "entity.hpp"
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"

#include "effected.hpp"

using namespace WVM;

std::shared_ptr<Entity> create_bob(ISystemManager& manager, IFactoryManager& f_manager);
std::shared_ptr<Entity> create_tank(ISystemManager& manager, IFactoryManager& f_manager);


