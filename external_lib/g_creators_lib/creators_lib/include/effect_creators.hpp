#pragma once
#include <memory>
#include "entity.hpp"
#include "i_sys_manager.hpp"

#include"effected.hpp"

using namespace WVM;


std::shared_ptr<Effect> create_poisoning(std::shared_ptr<Effected> target);
std::shared_ptr<Effect> create_weakening(std::shared_ptr<Effected> target);
std::shared_ptr<Effect> create_slowdown(std::shared_ptr<Effected> target);