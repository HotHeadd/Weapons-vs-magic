#pragma once
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace WVM
{

class Persistable{
public:
    virtual json save() = 0;
    virtual void load(json&) = 0;
};

} // namespace WVM
