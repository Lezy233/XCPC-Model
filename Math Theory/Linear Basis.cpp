/**
 * @brief   Linear Basis  线性基
*/

#include <bits/stdc++.h>

template <class T, size_t P>
struct LinearBasis {
    int cnt = 0; // 基数量
    std::array<T, P> dig;
    LinearBasis(): dig{} {
        static_assert(
            (std::is_same<T, unsigned int>::value) ||
            (std::is_same<T, unsigned long long>::value),
            "Type T must be either unsigned int or unsigned long long"
        );
    }

    void insert(T t) {
        if(cnt == int(P)) return;
        for(int j=P-1; ~j; --j){
            if(!(t&1ULL<<j)) continue;
            if(dig[j]){ t ^= dig[j]; continue; }

            for(int k=0; k<j; ++k) if(t&1LL<<k) t ^= dig[k];
            for(int k=j+1; k<P; ++k) if(dig[k]&1LL<<j) dig[k] ^= t;
            dig[j] = t;
            ++cnt;
            break;
        }
    }

    void insert(const LinearBasis &other) {
        for(auto &i:other.dig) insert(i);
    }
    
    static LinearBasis merge(const LinearBasis &lhs, const LinearBasis &rhs) {
        LinearBasis ans = lhs;
        for(auto &i:rhs.dig) ans.insert(i);
        return ans;
    }

    T queryMax() {
        long long ans = 0;
        for(auto &i:dig) ans ^= i;
        return ans;
    }

    bool find(const T &k) {
        T cur = 0;
        for(int i=P-1; ~i; --i){
            if((cur^k)&1ULL<<i){
                if(dig[i]==0) return false;
                cur ^= dig[i];
            }
        }
        return cur == k;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; std::cin>>n;
    // LinearBasis<64> LB;
    // LinearBasis<64>::merge();
    LinearBasis<unsigned long long,50> LB;
    while(n--){
        long long x; std::cin>>x;
        LB.insert(x);
    }
    std::cout<<LB.queryMax()<<"\n";
    return;
}


/* template <int P>
struct LinearBasis {
    std::vector<long long> dig;
    LinearBasis(std::vector<long long> &_init): dig(0) {
        std::array<long long,P> tt={};
        for(auto &t:_init){
            for(int j=P;j>=0;--j){
                if(!(t&1LL<<j)) continue;
                if(dig[j]){ t^=dig[j]; continue; }

                for(int k=0;k<j;++k) if(t&1LL<<k) t^=dig[k];
                for(int k=j+1;k<=P;++k) if(dig[k]&1LL<<j) dig[k]^=t;
                dig[j]=t;
                break;
            }
        }
        for(auto &i:tt) if(i) dig.emplace_back(i);
    }
}; */