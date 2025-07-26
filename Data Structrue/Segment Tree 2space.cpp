#include <bits/stdc++.h>

// 该线段树每个节点的下标为该节点在树中的dfn序+1

template <class Info,class Tag>
class SegmentTree {
private:
    #define rt (rtL+rtR|rtL!=rtR)
    #define mid ((rtL+rtR)>>1)
    #define ls index(rtL,mid)
    #define rs index(mid+1,rtR)

    int n;
    std::vector<Info>info;
    std::vector<Tag>tag;

    inline int index(int L,int R) {
        return L+R|L!=R;
    }

    void push_up(int rtL,int rtR) {
        info[rt]=info[ls]+info[rs];
    }

    void addTag(int rtL,int rtR,const Tag&v) {
        info[rt].apply(v);
        tag[rt].apply(v);
    }

    void push_down(int rtL,int rtR) {
        addTag(rtL,mid,tag[rt]);
        addTag(mid+1,rtR,tag[rt]);
        tag[rt]=Tag();
    }

    void _pointUpdate(int rtL,int rtR,int pos,const Info &v) { // 单点修改
        if(rtR==rtL){ info[rt]=v; return; }
        push_down(rtL,rtR);
        if(pos<=mid) _pointUpdate(rtL,mid,pos,v);
        else _pointUpdate(mid+1,rtR,pos,v);
        push_up(rtL,rtR);
    }

    void _rangeUpdate(int rtL,int rtR,int L,int R,const Tag &v) { // 区间加Tag
        if(rtL>R||rtR<L) return;
        if(rtL>=L&&rtR<=R){ addTag(rtL,rtR,v); return; }
        push_down(rtL,rtR);
        _rangeUpdate(rtL,mid,L,R,v);
        _rangeUpdate(mid+1,rtR,L,R,v);
        push_up(rtL,rtR);
    }

    Info _rangeQuery(int rtL,int rtR,int L,int R) {
        if(L>rtR||R<rtL) return Info();
        if(L<=rtL&&R>=rtR) return info[rt];
        push_down(rtL,rtR);
        return _rangeQuery(rtL,mid,L,R)+_rangeQuery(mid+1,rtR,L,R);
    }

public:
    SegmentTree(int _n): n(_n), info(_n<<1|1), tag(_n<<1|1) {}
    SegmentTree(std::vector<Info>_init): SegmentTree(_init.size()) {
        auto build=[&](auto self,int rtL,int rtR){
            if(rtL==rtR){ info[rt]=_init[rtL-1]; return; }
            self(self,rtL,mid); self(self,mid+1,rtR);
            push_up(rtL,rtR);
        };
        build(build,1,n);
    }

    void pointUpdate(int pos,const Info &v){ _pointUpdate(1,1,n,pos,v); }
    void rangeUpdate(int L,int R,const Tag &v){ _rangeUpdate(1,n,L,R,v); }
    Info rangeQuery(int L,int R){ return _rangeQuery(1,n,L,R); }
    #undef rt, ls, rs, mid
};

struct Tag {
    long long add;
    void apply(Tag t) {
        add+=t.add;
    }
};

struct Info {
    int cnt;
    long long sum=0;
    Info(): cnt(1) {}
    void apply(Tag t) {
        sum+=t.add*cnt;
    }
};

Info operator+(Info a,Info b) {
    Info c;
    c.cnt=a.cnt+b.cnt;
    c.sum=a.sum+b.sum;
    return c;
}