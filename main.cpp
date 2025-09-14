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


int slow_get_page_int(int key) { return key; }

template <typename T, typename KeyT>
template <typename F>
bool cache_t<T, KeyT>::lookup_update(KeyT key, F slow_get_page) {
    auto hit = hash_.find(key);
    if (hit == hash_.end()) {
        std::cout<<" - no hit | ";
        if (full()) {
            hash_.erase(cache_.back());
            cache_.pop_back();
        }
        cache_.push_front(slow_get_page(key));
        hash_[key] = cache_.begin();
        return false;
    }
    std::cout<<" - hit | ";
    auto eltit = hit->second;

    if (eltit != cache_.begin())
        cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
    return true;
}
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