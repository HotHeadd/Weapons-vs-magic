#pragma once
#include <memory>
#include "entity.hpp"
#include "i_sys_manager.hpp"
#include "i_factory_manager.hpp"

#include"effected.hpp"

using namespace WVM;


std::shared_ptr<Effect> poisoning_timetest(std::shared_ptr<Effected> target);
std::shared_ptr<Effect> slowdown_timetest(std::shared_ptr<Effected> target);

std::shared_ptr<Entity> bob_timetest(ISystemManager& manager, IFactoryManager& f_manager);

std::shared_ptr<Entity> magic_tower_timetest(ISystemManager& manager, IFactoryManager& f_manager, TowerNode&);