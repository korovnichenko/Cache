#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT>
struct cache_t {
    size_t sz_;
    std::list<T> cache_;

    using ListIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    cache_t(size_t Size) {sz_ = Size;}
    bool full(){
        return cache_.size() == sz_;
    }
    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page);

};

template bool cache_t<int, int>::lookup_update<int (int)>(int key, int (*slow_get_page)(int));
