// P3834
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"

constexpr int N=2e5+5;

int root[N], tot=0; // root[i]指向tree
struct Info{
    int ls,rs,cnt;
}info[N<<5];

#define ls(rt) info[rt].ls
#define rs(rt) info[rt].rs
#define mid (rtL+rtR>>1)

int update(int pre, int rtL, int rtR, int pos) {
    int rt=++tot;
    info[rt]=info[pre]; ++info[rt].cnt;
    if(rtL<rtR){
        if(pos<=mid) ls(rt)=update(ls(pre),rtL,mid,pos);
        else rs(rt)=update(rs(pre),mid+1,rtR,pos);
    }
    return rt;
}

int rangeQuery(int _l, int _r, int rtL, int rtR, int L, int R) {
    if(L<=rtL && rtR<=R) return info[_r].cnt-info[_l].cnt;
    int ans=0;
    if(L<=mid) ans+=rangeQuery(ls(_l),ls(_r),rtL,mid,L,R);
    if(R>mid)  ans+=rangeQuery(rs(_l),rs(_r),mid+1,rtR,L,R);
    return ans;
}
#undef ls
#undef rs
#undef mid

/*
class Persistent_SegmentTree {
private:
    struct Info { int ls,rs,cnt; };
    int tot,n;
    std::vector<Info> info;

    #define ls(rt) info[rt].ls
    #define rs(rt) info[rt].rs
    int _rangeQuery(int _l, int _r, int rtL, int rtR, int L, int R) {
        if(L<=rtL && rtR<=R) return info[_r].cnt-info[_l].cnt;
        int ans = 0;
        auto mid = std::midpoint(rtL, rtR);
        if(L<=mid) ans += _rangeQuery(ls(_l), ls(_r), rtL, mid, L, R);
        if(R>mid)  ans += _rangeQuery(rs(_l), rs(_r), mid+1, rtR, L, R); 
        return ans;
    }

    int _update(int pre, int rtL, int rtR, int pos) {
        int rt = info.size();
        info.emplace_back(info[pre]);
        ++info[rt].cnt;
        if(rtL < rtR) {
            auto mid = std::midpoint(rtL, rtR);
            if(pos<=mid) ls(rt) = _update(ls(pre), rtL, mid, pos);
            else         rs(rt) = _update(rs(pre), mid+1, rtR, pos);
        }
        return rt;
    }
public:
    Persistent_SegmentTree(int _n): n(_n), tot(0), info(1) {}
    int update(int pre, int pos) { return _update(pre, 1, n, pos); }
    int rangeQuery(int l, int r, int L, int R) { return _rangeQuery(l,r,1,n,L,R); }   
};

*/

/**
 * @brief   支持区间修改的可持久化线段树
 * @note    对于保存版本的操作需要手动进行，即 .root.push_back(.rangeUpdate(...))
 */
template <typename T>
class Persistent_SegmentTree {
private:
    struct Info{ int ls,rs; T val, tag; };
    int n;
    std::vector<Info> info;

    #define ls(rt) info[rt].ls
    #define rs(rt) info[rt].rs
    #define mid (rtL+rtR>>1)
    
    // 对单个时间点的区间询问
    T _point_rangeQuery(int rt, int rtL, int rtR, int L, int R, T preTag) {
        if(L == rtL && rtR==R) return info[rt].val+preTag*(R-L+1);
        T nowTag = preTag + info[rt].tag;
        if(R<=mid) return _point_rangeQuery(ls(rt),rtL,mid,L,R,nowTag);
        if(L>mid)  return _point_rangeQuery(rs(rt),mid+1,rtR,L,R,nowTag);
        return _point_rangeQuery(ls(rt),rtL,mid,L,mid,nowTag)
              +_point_rangeQuery(rs(rt),mid+1,rtR,mid+1,R,nowTag);
    }
    // (_l,_r]时间点的[L,R]之和
    T _range_rangeQuery(int _l, int _r, int rtL, int rtR, int L, int R, T preTag_l, T preTag_r) {
        if(L==rtL && rtR==R) return info[_r].val-info[_l].val+(preTag_r-preTag_l)*(R-L+1);
        T nowTag_l = preTag_l+info[_l].tag, nowTag_r = preTag_r+info[_r].tag;
        if(R<=mid) return _range_rangeQuery(ls(_l),ls(_r),rtL,mid,L,R,nowTag_l,nowTag_r);
        if(L>mid)  return _range_rangeQuery(rs(_l),rs(_r),mid+1,rtR,L,R,nowTag_l,nowTag_r);
        return _range_rangeQuery(ls(_l),ls(_r),rtL,mid,L,mid,nowTag_l,nowTag_r)
              +_range_rangeQuery(rs(_l),rs(_r),mid+1,rtR,mid+1,R,nowTag_l,nowTag_r);
    }
    // [L,R] += d
    int _rangeUpdate(int pre, int rtL, int rtR, int L, int R, T d) { 
        int rt = info.size();
        info.emplace_back(info[pre]);
        info[rt].val += d*(R-L+1);
        if(L==rtL && rtR==R){
            info[rt].tag += d;
            return rt;
        }
        if(R<=mid) ls(rt) = _rangeUpdate(ls(pre),rtL,mid,L,R,d);
        else if(L>mid) rs(rt) = _rangeUpdate(rs(pre),mid+1,rtR,L,R,d);
        else{
            ls(rt) = _rangeUpdate(ls(pre),rtL,mid,L,mid,d);
            rs(rt) = _rangeUpdate(rs(pre),mid+1,rtR,mid+1,R,d);
        }
        return rt;
    }

public:
    std::vector<int>root;
    Persistent_SegmentTree(int _n): n(_n), root(1), info(1) {}
    int rangeUpdate(int pre, int L, int R, T d){ return _rangeUpdate(pre,1,n,L,R,d); }
    T Point_rangeQuery(int rt, int L, int R){ return _point_rangeQuery(rt,1,n,L,R,0); }
    T Range_rangeQuery(int l, int r, int L, int R){ return _range_rangeQuery(l,r,1,n,L,R,0,0); }
    #undef ls
    #undef rs
    #undef mid
};

