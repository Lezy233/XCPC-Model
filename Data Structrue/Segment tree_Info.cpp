#include <bits/stdc++.h>
/**
 * @brief   线段树（单点修改，区间查询） 抄的jiangly板子
 * @note    此处查询是[L,R), 遵循的是数组
*/
template <class Info>
class SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    std::vector<Info> info;

    void push_up(int rt) {
        info[rt] = info[ls] + info[rs];
    }

    void _update(int rt, int rtL, int rtR, int pos, const Info &v) {
        if (rtR-rtL == 1) { info[rt] = v; return; }
        auto mid = std::midpoint(rtL, rtR);
        if (pos < mid) _update(ls, rtL, mid, pos, v);
        else _update(rs, mid, rtR, pos, v);
        push_up(rt);
    }

    Info _query(int rt, int rtL, int rtR, int L, int R) {
        if (rtR <= L || R <= rtL) return Info();
        if (L <= rtL && R >= rtR) return info[rt];
        Info res = Info();
        auto mid = std::midpoint(rtL, rtR);
        if (L < mid && R > mid) res = _query(ls, rtL, mid, L, R) + _query(rs, mid, rtR, L, R);
        else if (L < mid) res = _query(ls, rtL, mid, L, R);
        else res = _query(rs, mid, rtR, L, R);
        return res;
    }
public:
    int n;
    SegmentTree(int _n, Info _v=Info()): n(_n), info(4<<std::__lg(_n)) {
        auto build = [&](auto self, int rt, int rtL, int rtR) {
            if (rtR-rtL == 1) { info[rt] = _v; return; }
            auto mid = std::midpoint(rtL, rtR);
            self(self, ls, rtL, mid);
            self(self, rs, mid, rtR);
            push_up(rt);
        };
        build(build, 1, 0, _n);
    }
    SegmentTree(std::vector<Info>&_init): n(_init.size()), info(4<<std::__lg(_init.size())) {
        auto build = [&](auto self, int rt, int rtL, int rtR) {
            if (rtR-rtL == 1) { info[rt] = _init[rtL]; return; }
            auto mid = std::midpoint(rtL, rtR);
            self(self, ls, rtL, mid);
            self(self, rs, mid, rtR);
            push_up(rt);
        };
        build(build, 1, 0, n);
    }

    void update(int pos, const Info &v) { _update(1, 0, n, pos, v); }
    Info query(int L, int R) { return _query(1, 0, n, L, R); }
    #undef ls
    #undef rs
};

struct Info {
    int cnt, min;
    Info(): cnt(1), min(-1) {}
    Info(int w): cnt(1), min(w) {}
};

inline Info operator+(const Info &a, const Info &b) {
    Info c;
    c.cnt = a.cnt + b.cnt;
    c.min = std::min(a.min, b.min);
    return c;
}

/* 
// 这个版本使用 [1,n] 为了方便树套树使用
template <class Info>
class SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    #define mid (rtL+rtR>>1)
    std::vector<Info>info;

    void push_up(int rt) {
        info[rt]=info[ls]+info[rs];
    }

    void init(int _n, Info _v=Info()) {
        init(std::vector(_n,_v));
    }

    void init(std::vector<Info>&_init) {
        n=_init.size();
        info.assign(4<<std::__lg(n), Info());
        auto build=[&](auto self,int rt,int rtL,int rtR){
            if (rtL==rtR){ info[rt]=_init[rtL]; return; }
            self(self,ls,rtL,mid);
            self(self,rs,mid+1,rtR);
            push_up(rt);
        };
        build(build,1,1,n);
    }

    void _update(int rt,int rtL,int rtR,int pos,const Info &v) {
        if (rtL==rtR){ info[rt]=v; return; }
        if (pos<=mid) _update(ls,rtL,mid,pos,v);
        else _update(rs,mid+1,rtR,pos,v);
        push_up(rt);
    }

    Info _query(int rt,int rtL,int rtR,int L,int R) {
        if (rtR<L||R<rtL) return Info();
        if (L<=rtL&&R>=rtR) return info[rt];
        Info res=Info();
        if (L<=mid&&R>mid) res=_query(ls,rtL,mid,L,R)+_query(rs,mid+1,rtR,L,R);
        else if (L<=mid) res=_query(ls,rtL,mid,L,R);
        else res=_query(rs,mid+1,rtR,L,R);
        return res;
    }
    #undef ls
    #undef rs
    #undef mid

public:
    int n;
    SegmentTree(): n(0) {}
    SegmentTree(int _n): n(_n), info(4<<std::__lg(_n)) {}
    SegmentTree(int _n, Info _v=Info()) { init(_n,_v); }
    SegmentTree(std::vector<Info>&_init) { init(_init); }

    void update(int pos,const Info &v) { _update(1,1,n,pos,v); }
    Info query(int L,int R) { return _query(1,1,n,L,R); }
};

struct Info {
    int cnt, min;
    Info(): cnt(1),min(-1) {}
    Info(int w): cnt(1), min(w) {}
};

Info operator+(Info a,Info b) {
    Info c;
    c.cnt=a.cnt+b.cnt;
    c.min=std::min(a.min,b.min);    
    return c;
}
 */