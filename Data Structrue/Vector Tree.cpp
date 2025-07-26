/**
 * @brief   类平衡树，玄学复杂度，在树套树里运行地很快
 * @warning 不保证时间复杂度的正确性
*/
#include <bits/stdc++.h>

template <typename T>
struct VecTree {
    std::vector<T>vec;
    void insert(T val){ vec.insert(std::ranges::lower_bound(vec,val),val); }
    void del(T val){ vec.erase(std::ranges::lower_bound(vec,val)); }
    int queryRank(T val){ return std::ranges::lower_bound(vec,val)-vec.begin()+1; }
    T queryPre(T val) {
        auto it=std::ranges::lower_bound(vec,val);
        return it==vec.begin()? -2147483647:(*--it);
    }
    T queryNxt(T val) {
        auto it=std::ranges::upper_bound(vec,val);
        return it==vec.end()? 2147483647:*it;
    }
};