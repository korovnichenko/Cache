#include <iostream>
#include <list>
#include <unordered_map>
#include "cache.hpp"


int slow_get_page_int(int key) { return key; }


int main() {
    int Size;
    std::cout<<"Choose size of cache: ";
    std::cin>>Size;
    cache_t<int, int> cache(Size);
    int data[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    for(int number: data){
        std::cout<<number;
        cache.lookup_update<typeof slow_get_page_int>(number, slow_get_page_int);
        
    }
    return 0;
}