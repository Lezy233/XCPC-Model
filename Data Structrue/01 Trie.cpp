// P4551
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef std::pair<int,int> PII;

template <class T>
class Trie {
private:
    struct Info {
        std::array<Info*, 2> son;
        Info(): son{} {}
    };
    Info *root;
    size_t TOT;
public:
    Trie(): root(new Info()), TOT((std::is_same_v<T, unsigned>) ? 31 : 63) {
        static_assert(
            (std::is_same_v<T, unsigned int>) ||
            (std::is_same_v<T, unsigned long long>),
            "Type T must be either unsigned int or unsigned long long"
        );
    }
    
    void insert(T x) {
        Info *cur = root;
        for(unsigned i = TOT; ~i; --i) {
            int c = x>>i&1;
            if(cur->son[c] == nullptr) cur->son[c] = new Info();
            cur = cur->son[c];
        }
    }
    
    T getMax(int x) {
        Info *cur = root;
        T ans = 0;
        for(unsigned i = TOT; ~i; --i) {
            int c = x>>i&1;
            if(cur->son[c^1]) {
                ans |= 1ULL<<i;
                cur = cur->son[c^1];
            } else {
                cur = cur->son[c];
            }
        }
        return ans;
    }
};

/*
在 01Trie 上面操作的时候，使用 vector 模拟的 Trie 拓展性更高
template <class T>
class Trie {
private:
    struct Info {
        std::array<int, 2> son;
        Info(): son{} {}
    };
    std::vector<Info> info;
    const unsigned TOT;
public:
    Trie(): info(2), TOT((std::is_same_v<T, unsigned>) ? 31 : 63) {
        static_assert(
            (std::is_same_v<T, unsigned int>) ||
            (std::is_same_v<T, unsigned long long>),
            "Type T must be either unsigned int or unsigned long long"
        );
    }
    
    void insert(T x) {
        int cur = 1;
        for(unsigned i = TOT; ~i; --i) {
            int c = x>>i&1;
            if(info[cur].son[c] == 0) {
                info[cur].son[c] = info.size();
                info.emplace_back();
            }
            cur = info[cur].son[c];
        }
    }
    
    T getMax(int x) {
        int cur = 1;
        T ans = 0;
        for(unsigned i = TOT; ~i; --i) {
            int c = x>>i&1;
            if(info[cur].son[c^1]) {
                ans |= 1ULL<<i;
                cur = info[cur].son[c^1];
            } else {
                cur = info[cur].son[c];
            }
        }
        return ans;
    }
};
 */