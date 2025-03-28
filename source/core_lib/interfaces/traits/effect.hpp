#pragma once

#include <memory>
#include "object.hpp"

namespace WVM
{

class Effect : public Object{
public:
    virtual ~Effect() = default;
    virtual unsigned turns_to_last() const = 0;
    virtual void set_duration(unsigned new_duration) = 0;
    virtual unsigned strength() const = 0;
    virtual void set_strength(unsigned new_strength) = 0;

    virtual std::string_view type() = 0;
    
    virtual void inflict() = 0;
    virtual void neutralize() = 0;

protected:
};  

} // namespace WVM
