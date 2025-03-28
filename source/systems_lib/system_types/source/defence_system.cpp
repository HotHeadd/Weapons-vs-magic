#include "defence_system.hpp"
#include "i_sys_manager.hpp"
#include <future>

namespace WVM
{

DefenceSystem::DefenceSystem(ISystemManager& manager) noexcept : manager_(manager) {}

void DefenceSystem::update(){
    std::vector<std::shared_ptr<IDefence>> to_remove;
    std::mutex removal_mutex;

    size_t thread_count = std::thread::hardware_concurrency();
    if (!thread_count){
        thread_count = 4;
    }
    const size_t chunk_size = (defence_.size() + thread_count - 1)/thread_count;
    std::vector<std::future<void>> futures;
    if (chunk_size < thread_count){
        thread_count = chunk_size;
    }

    auto it = defence_.begin();
    for (size_t i=0; i< thread_count; ++i){
        auto start = it;
        std::advance(it, (i == thread_count-1) ? std::distance(it, defence_.end()) : chunk_size);
        auto end = it;
        futures.emplace_back(std::async(std::launch::async, [&, start, end](){
            for (auto iter = start; iter != end; ++iter){
                auto defence = *iter;
                if (defence->is_dead()){
                    std::lock_guard<std::mutex> lock(removal_mutex);
                    to_remove.push_back(defence);
                }
                else{
                    defence->update();
                }
            }
        }));
    }

    for (auto& future : futures) {
        future.get();
    }
    for (const auto& defence : to_remove) {
        do_remove(defence);
        defence->on_death();
    }
}

void DefenceSystem::refresh(){
    for (auto& defence : defence_){
        defence->reset_cooldown();
    }
}

bool DefenceSystem::check_type(const Entity* ptr){
    return dynamic_cast<const IDefence*>(ptr) != nullptr;
}

void DefenceSystem::do_remove(std::shared_ptr<void> obj){
    std::shared_ptr<IDefence> defence = std::static_pointer_cast<IDefence>(obj);
    if (!defence_.contains(defence)){
        throw std::runtime_error("Defence not in defence");
    }
    defence_.erase(defence);
}

void DefenceSystem::do_add(std::shared_ptr<void> obj){
    std::shared_ptr<IDefence> defence = std::static_pointer_cast<IDefence>(obj);
    if (defence_.contains(defence)){
        throw std::runtime_error("Defence not in defence");
    }
    defence_.insert(defence);

    if (defence_.contains(defence)){
    }
}

std::unordered_set<std::shared_ptr<IDefence>>& DefenceSystem::get_defence(){
    return defence_;
};

bool DefenceSystem::is_empty(){
    return defence_.empty();
}

} // namespace WVM
