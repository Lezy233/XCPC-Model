#include <bits/stdc++.h>
#include <bits/extc++.h>

struct Hash
{
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x^x>>30)*0xbf58476d1ce4e5b9;
        x = (x^x>>27)*0x94d049bb133111eb;
        return x^x>>31;
    }

    static size_t get(const uint64_t x) {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED_RANDOM);
    }

    template <typename T>
    size_t operator()(T x) const {
        return get(std::hash<T>()(x));
    }

    template <typename F,typename S>
    size_t operator()(std::pair<F,S> p) const {
        return get(std::hash<F>()(p.first))^std::hash<S>()(p.second);
    }
};

int main()
{
    std::unordered_map<std::pair<int,int>,int,Hash>mp;
    
    // or choose gp_hash_table or cc_hash_table
    // do not forget to include <bits/extc++.h>
    __gnu_pbds::gp_hash_table<std::pair<int,int>,int,Hash>mp2;
    __gnu_pbds::cc_hash_table<std::pair<int,int>,int,Hash>mp3;

}