#include<bits/stdc++.h>

template <typename T>
class SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    #define mid ((rtL+rtR)>>1)
    std::vector<T> tree, tag;

    void push_up(int rt) {
        tree[rt]=tree[ls]+tree[rs];
    }

    void addtag(int rt,int rtL,int rtR,T d) {
        tag[rt]+=d;
        tree[rt]+=d*(rtR-rtL);
    }

    void push_down(int rt,int rtL,int rtR) {
        if(tag[rt]){
            addtag(ls,rtL,mid,tag[rt]);
            addtag(rs,mid,rtR,tag[rt]);
            tag[rt]=0;
        }
    }

    void _rangeUpdate(int rt,int rtL,int rtR,int L,int R,T d) {
        if(L>=rtR||R<=rtL) return;
        if(L<=rtL&&rtR<=R){ addtag(rt,rtL,rtR,d); return; }
        push_down(rt,rtL,rtR);
        if(L<mid) _rangeUpdate(ls,rtL,mid,L,R,d);
        if(R>mid) _rangeUpdate(rs,mid,rtR,L,R,d);
        push_up(rt);
    }

    T _rangeQuery(int rt,int rtL,int rtR,int L,int R) {
        if(L<=rtL&&rtR<=R) return tree[rt];
        push_down(rt,rtL,rtR);
        T res=0;
        if(L<mid) res+=_rangeQuery(L,R,ls,rtL,mid);
        if(R>mid) res+=_rangeQuery(L,R,rs,mid,rtR);
        return res;
    }

public:
    int n;
    SegmentTree(int _n): n(_n), tree(_n<<2|3), tag(_n<<2|3) {}
    SegmentTree(int _n,std::vector<T>&_init): n(_n), tree(_n<<2|3), tag(_n<<2|3) {
        auto build=[&](auto self,int rt,int rtL,int rtR)->void{
            if(rtR-rtL==1){ tree[rt]=_init[rtL]; return; }
            if(rtL<mid) self(self,ls,rtL,mid);
            if(rtR>mid) self(self,rs,mid,rtR);
            push_up(rt);
        };
        build(build,1,0,_n);
    }

    void rangeUpdate(int L, int R, T t){ _rangeUpdate(1,0,n,L,R); }
    T rangeQuery(int L, int R){ return _rangeQuery(1,0,n,L,R); }
    #undef ls, rs, mid
};


/*
// [l,r]
template <typename T>
class SegmentTree {
    // 支持区间加法，带Lazy-tag
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    #define mid ((rtL+rtR)>>1)
    std::vector<T>tree, tag;

    void push_up(int rt) {
        tree[rt]=std::max(tree[ls],tree[rs]);
    }

    void addtag(int rt,int rtL,int rtR,T d) {
        tag[rt]+=d;
        tree[rt]+=d;
    }

    void push_down(int rt,int rtL,int rtR) {
        if(tag[rt]){
            addtag(ls,rtL,mid,tag[rt]);
            addtag(rs,mid+1,rtR,tag[rt]);
            tag[rt]=0;
        }
    }

    void _rangeUpdate(int rt,int rtL,int rtR,int L,int R,T d) {
        if(L<=rtL&&rtR<=R){ addtag(rt,rtL,rtR,d); return; }
        push_down(rt,rtL,rtR);
        if(L<=mid) _rangeUpdate(ls,rtL,mid,L,R,d);
        if(R>mid) _rangeUpdate(rs,mid+1,rtR,L,R,d);
        push_up(rt);
    }

    T _rangeQuery(int rt,int rtL,int rtR,int L,int R) {
        if(L<=rtL&&rtR<=R) return tree[rt];
        push_down(rt,rtL,rtR);
        T res=-1e30;
        if(L<=mid) res=std::max(_rangeQuery(ls,rtL,mid,L,R),res);
        if(R>mid) res=std::max(_rangeQuery(rs,mid+1,rtR,L,R),res);
        return res;
    }

    void build(int rt,int rtL,int rtR,T *v) {
        tag[rt]=0;
        if(rtL==rtR){ tree[rt]=v[rtL]; return; }
        build(ls,rtL,mid,v); build(rs,mid+1,rtR,v);
        push_up(rt);
    }

public:
    int n;

    SegmentTree(int _n): n(_n), tree(_n<<2|3), tag(_n<<2|3) {}
    SegmentTree(int _n,T *v): n(_n), tree(_n<<2|3), tag(_n<<2|3) {
        build(1,1,n,v);
    }

    void rangeUpdate(int L,int R,T d){ _rangeUpdate(1,1,n,L,R,d); }
    T rangeQuery(int L,int R){ return _rangeQuery(1,1,n,L,R); }
    #undef ls, rs, mid
};
*/

// 线段树，支持动态开点
template <typename T>
class SegmentTree {
private:
    struct Info{ int ls,rs,Max; };
    T n;
    std::vector<Info> info;

    #define ls(rt) info[rt].ls
    #define rs(rt) info[rt].rs
    #define mid (rtL+rtR>>1)
    int update(int rt, ll rtL, ll rtR, ll pos, int val) {
        if(rt==0){
            rt = info.size();
            info.emplace_back(0,0,0);
        }
        cmax(info[rt].Max, val);
        if(rtL<rtR){
            if(pos<=mid) ls(rt) = update(ls(rt),rtL,mid,pos,val);
            else         rs(rt) = update(rs(rt),mid+1,rtR,pos,val);
        }
        return rt;
    }

    int _rangeQuery(int rt, ll rtL, ll rtR, ll L, ll R) {
        if(rt==0) return 0;
        if(L<=rtL && rtR<=R) return info[rt].Max;
        int ans=0;
        if(L<=mid) cmax(ans, _rangeQuery(ls(rt),rtL,mid,L,R));
        if(R>mid)  cmax(ans, _rangeQuery(rs(rt),mid+1,rtR,L,R));
        return ans;
    }

public:
    int root;
    SegmentTree(T _n): n(_n), root(0), info(1) {}
    
    void update(T pos, int val){ root = update(root,0,n,pos,val); }
    int rangeQuery(T L, T R){ return _rangeQuery(root,0,n,L,R); }   
};