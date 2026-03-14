/**
 * @brief   线段树分裂
 * @warning vector扩容时原来节点的引用传参全部失效，因此必须一次性扩容
 */

// P5494
#include <bits/stdc++.h>
using std::cin, std::cout, std::vector, std::array;
#define endl "\n"
typedef long long ll;

template <typename T>
class SegmentTree {
private:
    #define ls(rt) info[rt].l
    #define rs(rt) info[rt].r
    #define mid (rtL+rtR>>1)

    struct Info{
        T cnt;
        int l,r;
        Info(T cnt_=0): cnt(cnt_), l(0), r(0) {}
    };

    int n, tot=0;
    std::vector<int>root;
    std::vector<Info>info; // std::vector<Info>info;

    void push_up(int rt) {
        info[rt].cnt=info[ls(rt)].cnt+info[rs(rt)].cnt;
    }

    int merge(int u,int v) { // 合并 u,v 返回父节点
        if(!u||!v) return u+v;
        info[v].cnt+=info[u].cnt;
        info[v].l=merge(info[u].l,info[v].l);
        info[v].r=merge(info[u].r,info[v].r);
        info[u]=Info();
        return v;
    }

    void split(int &u,int &v,int rtL,int rtR,int L,int R) { // [1,L)&&(R,N], [L,R]
        if(!u||rtL>R||rtR<L) return;
        if(L<=rtL&&rtR<=R){
            v=u; u=0;
            return;
        }
        if(!v) v=++tot;
        if(L<=mid) split(ls(u),ls(v),rtL,mid,L,R);
        if(R>mid) split(rs(u),rs(v),mid+1,rtR,L,R);
        push_up(u); push_up(v);
    }

    void _insert(int &rt,int rtL,int rtR,int pos,T val) {
        if(!rt) rt=++tot;
        info[rt].cnt+=val;
        if(rtL<rtR){
            if(pos<=mid) _insert(ls(rt),rtL,mid,pos,val);
            if(pos>mid) _insert(rs(rt),mid+1,rtR,pos,val);
        }
    }

    T _rangeQuery(int rt,int rtL,int rtR,int L,int R) {
        if(!rt) return 0;
        if(L>rtR||R<rtL) return 0;
        if(L<=rtL&&rtR<=R) return info[rt].cnt;
        T ans=0;
        if(L<=mid) ans+=_rangeQuery(ls(rt),rtL,mid,L,R);
        if(R>mid) ans+=_rangeQuery(rs(rt),mid+1,rtR,L,R);
        return ans;
    }

    int _rankQuery(int rt,int rtL,int rtR,T rank) {
        if(rtL==rtR) return rtL;
        T ls_cnt=info[ls(rt)].cnt;
        if(rank<=ls_cnt) return _rankQuery(ls(rt),rtL,mid,rank);
        return _rankQuery(rs(rt),mid+1,rtR,rank-ls_cnt);
    }

public:
    SegmentTree(unsigned int _n, std::vector<T>&_init): n(_n), root(2,0), info(_n*std::bit_width(_n+1)+3) {
        auto build=[&](auto self,int rtL,int rtR)->int{
            int rt=++tot;
            if(rtL==rtR){ info[rt].cnt=_init[rtL]; return rt; }
            info[rt].l=self(self,rtL,mid);
            info[rt].r=self(self,mid+1,rtR);
            push_up(rt);
            return rt;
        };
        root[1]=build(build,1,_n);
    }

    void mergeRange(int u,int v){ merge(root[u],root[v]); }
    void newRange(int id,int L,int R) {
        int newID=0;
        split(root[id],newID,1,n,L,R);
        root.emplace_back(newID);
    }

    void insert(int id,int pos,T val){ _insert(root[id],1,n,pos,val); }
    T rangeQuery(int id,int L,int R){ return _rangeQuery(root[id],1,n,L,R); }
    int rankQuery(int id,T rank){ return rank>info[root[id]].cnt? -1:_rankQuery(root[id],1,n,rank); }
    #undef ls, rs, mid
};

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; cin>>n>>m;
    vector<ll>cnt(n+1,0);
    for(int i=1;i<=n;++i) cin>>cnt[i];
    SegmentTree<ll>ST(n,cnt);
    while(m--){
        int opt,p,q,u,v,t,k;
        ll x;
        cin>>opt;
        switch(opt){
        case 0: cin>>p>>u>>v; ST.newRange(p,u,v); break;
        case 1: cin>>p>>t; ST.mergeRange(t,p); break;
        case 2: cin>>p>>x>>q; ST.insert(p,q,x); break;
        case 3: cin>>p>>u>>v; cout<<ST.rangeQuery(p,u,v)<<endl; break;
        case 4: cin>>p>>k; cout<<ST.rankQuery(p,k)<<endl; break;
        }
    }
    return 0;
}