#include <iostream>
#include <list>
#include <unordered_map>
#include "cache.hpp"

// template <typename T, typename KeyT>
// template <typename F>
// bool cache_t<T, KeyT>::lookup_update(KeyT key, F slow_get_page) {
//     auto hit = hash_.find(key);  
//     if (hit == hash_.end()) {
//         std::cout<<" - no hit | ";
//         if (full()) {
//             hash_.erase(cache_.back());
//             cache_.pop_back();
//         }
//         cache_.push_front(slow_get_page(key));
//         hash_[key] = cache_.begin();
//         return false;
//     }
//     std::cout<<" - hit | ";
//     auto eltit = hit->second;

//     if (eltit != cache_.begin())
//         cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
//     return true;
// }
// template <typename T, typename KeyT>
// KeyT cache_t<T, KeyT>::slowq_keyget(KeyT key){
//     auto hit = hash_.find(key);
//     if (hit == hash_.end()) {
//         std::cout<<"added to slow queue";
//         if (full()) {
//             hash_.erase(cache_.back());
//             cache_.pop_back();
//         }
//         hash_[key] = cache_.begin();
//         return 0;
//     }
//     std::cout<<"found in slow queue\n";
//     auto eltit = hit->second;
//     cache_.erase(eltit);
//     return key;
// }
