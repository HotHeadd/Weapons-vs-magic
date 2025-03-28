#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace WVM
{

class Object{
public:
    virtual ~Object() = default;
    virtual void on_death() = 0;

    virtual std::string_view type() = 0;
    virtual Object& set_type(std::string_view new_type) = 0;

    // virtual void save(std::string filename) = 0;
    // virtual void load() = 0;
};

} // namespace WVM
