#include <iostream>
#include <list>
#include <unordered_map>
#include "cache.hpp"


int slow_get_page_int(int key) { return key; }


int main() {
    int Size;
    std::cout<<"Choose size of cache: ";
    std::cin>>Size;
    int i = 1, hit = 0;
    cache_t<int, int> cache(Size);
    int data[] = { 2, 6, 1, 2, 1, 2, 1, 2};
    for(int number: data){
        std::cout<<"\n==============\n"<<i<<" iteration"<<"\n==============\n";
        std::cout<<number;
        // cache.slowq_keyget<typeof slow_get_page_int>(number, slow_get_page_int);
        // cache.lookup_update(number);
        hit += cache.Q2(number, slow_get_page_int);
        std::cout<<"A1in";
        cache.A1inprint();
        std::cout<<"A1out";
        cache.A1outprint();  
        std::cout<<"Am";
        cache.Amprint();
        i++;
    }
    std::cout<<"hit = "<<hit;
    return 0;
}