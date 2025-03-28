#pragma once

#include <typeindex>
#include <any>
#include <memory>
#include "../traits/entity.hpp"

namespace WVM
{

class ISystem{
public:
    virtual ~ISystem() = default;

    virtual void update() = 0;
    virtual void refresh() = 0;

    template <typename T>
    void add(std::shared_ptr<T> obj){
        if (check_type(obj.get())){
            do_add(std::move(obj));
        }
        else{
            throw std::runtime_error("Invalid object to add");
        }
    };

    template <typename T>
    void remove(std::shared_ptr<T> obj){
        if (check_type(obj.get())){
            do_remove(obj);
        }   
        else{
            throw std::runtime_error("Invalid object to remove");
        }
    };

    virtual bool is_empty() = 0;
protected:
    virtual bool check_type(const Entity* ptr) = 0;

    virtual void do_remove(std::shared_ptr<void> obj) = 0;
    virtual void do_add(std::shared_ptr<void> obj) = 0;
};

} // namespace WVM