#include <bits/stdc++.h>

// 线段树（区间修改，区间查询）
// 抄的jiangly板子
// 此处查询是[L,R), 遵循的是数组

template <class Info, class Tag>
class SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    std::vector<Info> info;
    std::vector<Tag> tag;

    void push_up(int rt) {
        info[rt] = info[ls] + info[rs];
    }

    void addTag(int rt, int rtL, int rtR, const Tag &v) {
        info[rt].apply(v);
        tag[rt].apply(v);
    }

    void push_down(int rt, int rtL, int rtR) {
        auto mid = std::midpoint(rtL, rtR);
        addTag(ls, rtL, mid, tag[rt]);
        addTag(rs, mid, rtR, tag[rt]);
        tag[rt] = Tag();
    }

    void _pointUpdate(int rt, int rtL, int rtR, int pos, const Info &v) { // 单点修改
        if(rtR-rtL == 1) { info[rt] = v; return; }
        push_down(rt, rtL, rtR);
        auto mid = std::midpoint(rtL, rtR);
        if(pos < mid) _pointUpdate(ls, rtL, mid, pos, v);
        else          _pointUpdate(rs, mid, rtR, pos, v);
        push_up(rt);
    }

    void _rangeUpdate(int rt, int rtL, int rtR, int L, int R, const Tag &v) {
        if(R <= rtL || rtR <= L) return;
        if(L <= rtL && rtR <= R) { addTag(rt, rtL, rtR, v); return; }
        if(rtR-rtL > 1) push_down(rt, rtL, rtR);
        auto mid = std::midpoint(rtL, rtR);
        _rangeUpdate(ls, rtL, mid, L, R, v);
        _rangeUpdate(rs, mid, rtR, L, R, v);
        if(rtR-rtL > 1) push_up(rt);
    }

    Info _rangeQuery(int rt, int rtL, int rtR, int L, int R) {
        if(L>=rtR || R<=rtL) return Info();
        if(L<=rtL && R>=rtR) return info[rt];
        push_down(rt, rtL, rtR);
        auto mid = std::midpoint(rtL, rtR);
        return _rangeQuery(ls, rtL, mid, L, R) + _rangeQuery(rs, mid, rtR, L, R);
    }

public:
    int n;
    SegmentTree(int _n): n(_n), info(4<<std::__lg(_n)), tag(4<<std::__lg(_n)) {}
    SegmentTree(const std::vector<Info> &_init): SegmentTree(_init.size()) {
        auto build = [&](auto self, int rt, int rtL, int rtR)->void {
            if(rtR-rtL == 1) { info[rt] = _init[rtL]; return; }
            auto mid = std::midpoint(rtL, rtR);
            self(self, ls, rtL, mid);
            self(self, rs, mid, rtR);
            push_up(rt);
        };
        build(build, 1, 0, n);
    }

    void pointUpdate(int pos, const Info &v) { _pointUpdate(1,0,n,pos,v); }
    void rangeUpdate(int L, int R, const Tag &v) { _rangeUpdate(1,0,n,L,R,v); }
    Info rangeQuery(int L, int R) { return _rangeQuery(1,0,n,L,R); }
};

// 下面的代码维护区间最大值，支持区间加、区间赋值
constexpr int64_t NOT_EXIST = -1;

struct Tag {
    int64_t plus, chg;
    Tag(): plus(0), chg(NOT_EXIST){}
    Tag(int64_t _plus, int64_t _chg): plus(_plus), chg(_chg) {}
    void apply(Tag t) {
        if(t.chg != NOT_EXIST) { plus = 0; chg = t.chg; }
        plus += t.plus;
    }
};

struct Info {
    int64_t Max = NOT_EXIST;
    Info() {}
    void apply(Tag t) {
        if(t.chg != NOT_EXIST) Max = t.chg;
        Max += t.plus;
    }
};

inline Info operator+(const Info &a, const Info &b) {
    Info c;
    c.Max = std::max(a.Max, b.Max);
    return c;
}