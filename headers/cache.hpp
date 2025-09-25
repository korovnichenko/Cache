#pragma once

#include <iostream>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT>
struct cache_t {
    size_t sz_Am, sz_A1in, sz_A1out;
    std::list<T> Am, A1in;
    std::list<KeyT> A1out;

    using ListIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListIt> hash_Am, hash_A1in, hash_A1out;

    cache_t(size_t Size) {
        sz_A1in = Size / 4;
        sz_Am = Size - sz_A1in;
        sz_A1out = Size / 2;
    }

    bool full_Am(){
        return Am.size() == sz_Am; //+
    }
    bool full_A1in(){
        return A1in.size() == sz_A1in; //+
    }
    bool full_A1out(){
        return A1out.size() == sz_A1out; //+
    }
    void Amprint(){ //+
        if(!(Am.empty())){
            std::cout<<":    ";
            for(auto elem: Am)
                std::cout<<elem<<" ";
            std::cout<<"\n";
        }
        else
            std::cout<<"     is empty\n";
    }
        void A1outprint(){ //+
        if(!(A1out.empty())){
            std::cout<<": ";
            for(auto elem: A1out)
                std::cout<<elem<<" ";
            std::cout<<"\n";
        }
        else
        std::cout<<"  is empty\n";
    }
    void A1inprint(){ //+
        if(!(A1in.empty())){
            std::cout<<":  ";
            for(auto elem: A1in)
                std::cout<<elem<<" ";
                std::cout<<"\n";
        }
        else
        std::cout<<" is empty\n";
    }
    template< typename F>
    bool Q2(KeyT key, F slow_get_page){
        //met in Am
        auto hit = hash_Am.find(key);
        if(hit != hash_Am.end()){
            std::cout<<" - hit | \n";
            auto eltit = hit->second;
            if (eltit != Am.begin())
                Am.splice(Am.begin(), Am, eltit, std::next(eltit));
            return true;
        }
        //met in A1out
        hit = hash_A1out.find(key);
        if(hit != hash_A1out.end()){
            //exchange elements between Am and A1out
            if(full_Am()){

                //getting key from Am and deleting it afterwards
                KeyT last_elem = Am.back();
                hash_Am.erase(last_elem);
                Am.pop_back();

                //adding new element with to the Am
                Am.push_front(key);
                hash_Am[key] = Am.begin();

                //swapping met key in A1out with one found earlier
                hash_A1out.erase(key);
                A1out.erase(hit->second);
                A1out.push_front(last_elem);
                hash_A1out[last_elem] = A1out.begin();
                return false;
            }
            Am.push_front(key);
            hash_Am[key] = Am.begin();
            A1out.erase(hit->second);
            hash_A1out.erase(key);

            return false;
        }

        //met in a1in
        hit = hash_A1in.find(key);
        if(hit != hash_A1in.end())
            return true;
        if (full_A1in()) {
       
            //element from A1in goes to A1out
            KeyT last_in = A1in.back();
            if (full_A1out()) {
                //deleting last element from A1out
                KeyT last_out = A1out.back();
                hash_A1out.erase(last_out);
                A1out.pop_back();
            }
            
            //erasing last from A1in
            hash_A1in.erase(last_in); 
            A1in.pop_back();

            //adding that element to A1out
            A1out.push_front(last_in);    
            hash_A1out[last_in] = A1out.begin();
            std::cout<<"added to warm queue\n";

        }

        //just adding new element to A1in
        std::cout<<" added to cold queue\n";
        A1in.push_front(slow_get_page(key));
        hash_A1in[key] = A1in.begin();
        std::cout<<"-----MISS-----\n";
        return false;
    }
};

//template bool cache_t<int, int>::lookup_update<int (int)>(int key, int (*slow_get_page)(int));
//template int cache_t<int, int>::slowq_keyget(int key); 