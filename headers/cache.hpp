#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT>
struct cache_t {
    size_t sz_Am, sz_A1in;
    std::list<T> Am, A1in;

    using ListIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListIt> hash_Am, hash_A1in;

    cache_t(size_t Size) {
        sz_Am = Size-Size/4;
        sz_A1in = Size/4;
    }

    bool full_Am(){
        return Am.size() == sz_Am;
    }
    bool full_A1in(){
        return A1in.size() == sz_A1in;
    }
    void Amprint(){
        if(!(Am.empty())){
            std::cout<<": ";
            for(auto elem: Am)
                std::cout<<elem<<" ";
            std::cout<<"\n";
        }
        else
            std::cout<<" list is empty\n ";
    }
    void A1inprint(){
        if(!(A1in.empty())){
            std::cout<<": ";
            for(auto elem: A1in)
                std::cout<<elem<<" ";
            std::cout<<"\n";
        }
        else
            std::cout<<" list is empty\n ";
    }

    // bool lookup_update(KeyT key){
    //     auto hit = hash_Am.find(key);
    //     if (hit == hash_.end()) {
    //         std::cout<<" - no hit | ";
    //         if (full_cache()) {
    //             hash_.erase((KeyT)Am.back());
    //             Am.pop_back();
    //         }
    //         Am.push_front(key);
    //         hash_[key] = Am.begin();
    //         return false;
    //     }
    //     std::cout<<" - hit | ";
    //     auto eltit = hit->second;
        
    //     if (eltit != Am.begin())
    //     Am.splice(A.begin(), Am, eltit, std::next(eltit));
    //     return true;
    //}
    // template <typename F>
    // bool slowq_keyget(KeyT key, F slow_get_page){
    //     auto hit = hash_.find(key);
    //     if (hit == hash_.end()) {
    //         std::cout<<"added to slow queue";
    //         if (full_A1in()) {
    //             hash_.erase((KeyT)A1in.back());
    //             A1in.pop_back();
    //         }
    //         A1in.push_front(slow_get_page(key));
    //         hash_[key] = A1in.begin();
    //         return false;
    //     }
        
    //     std::cout<<"found in slow queue\n";
    //     auto eltit = hit->second;
    //     Am.push_front(key);m
    //     //hash_.erase(hit);
    //     A1in.erase(eltit);
    //     return true;
    // }
    template< typename F>
    bool Q2(KeyT key, F slow_get_page){
        auto hit = hash_Am.find(key);
        if(hit == hash_Am.end()){
            hit = hash_A1in.find(key);
            if(hit == hash_A1in.end()){
                std::cout<<"added to slow queue\n";
                if (full_A1in()) {
                    hash_A1in.erase((KeyT)A1in.back());
                    A1in.pop_back();
                    std::cout<<"erase нахуй \n";
                }
                A1in.push_front(slow_get_page(key));
                hash_A1in[key] = A1in.begin();
                return false;
            }
            auto eltit = hit->second;
            if (eltit != A1in.begin())
                A1in.splice(A1in.begin(), A1in, eltit, std::next(eltit));
            return true;
        }
        std::cout<<" - hit | ";
        auto eltit = hit->second;
        if (eltit != Am.begin())
        Am.splice(Am.begin(), Am, eltit, std::next(eltit));
        return true;
    }
};

//template bool cache_t<int, int>::lookup_update<int (int)>(int key, int (*slow_get_page)(int));
//template int cache_t<int, int>::slowq_keyget(int key); 