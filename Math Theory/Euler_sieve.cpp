#include <bits/stdc++.h>

std::vector<bool> isPrime;
std::vector<int64_t> prime;

void Euler_sieve(int n) {
    isPrime.resize(n+1, true);
    isPrime[1] = false;
    for(int i=2; i<=n; ++i){
        if(isPrime[i]) prime.emplace_back(i);
        for(auto j:prime) {
            if(i*j > n) break;
            isPrime[i*j] = false;
            if(i%j == 0) break;
        }
    }
}
/* 
constexpr int N = 1e6;
std::array<bool, N+1> isPrime;
std::vector<int64_t> prime;
auto init = []{
    isPrime.fill(true);
    isPrime[1] = false;
    for(int i = 2; i <= N; ++i) {
        if(isPrime[i]) prime.emplace_back(i);
        for(auto j:prime) {
            if(i * j > N) break;
            isPrime[i * j] = false;
            if(i % j == 0) break;
        }
    }
    return 0;
}();
 */