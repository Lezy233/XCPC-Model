/**
 * @brief   Heavy Path Decomposition 树链剖分
 */

// P3384
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl std::endl
//#define endl "\n"

template <class Info, class Tag>
class SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    #define mid (rtL+rtR>>1)
    std::vector<Info> info;
    std::vector<Tag> tag;

    void push_up(int rt) {
        info[rt] = info[ls]+info[rs];
    }

    void addTag(int rt, const Tag &v) {
        info[rt].apply(v);
        tag[rt].apply(v);
    }

    void push_down(int rt) {
        addTag(ls,tag[rt]);
        addTag(rs,tag[rt]);
        tag[rt] = Tag();
    }

    void _pointUpdate(int rt, int rtL, int rtR, int pos, const Info &v) { // 单点修改
        if(rtR-rtL==1){ info[rt] = v; return; }
        push_down(rt);
        if(pos<mid) _pointUpdate(ls,rtL,mid,pos,v);
        else _pointUpdate(rs,mid,rtR,pos,v);
        push_up(rt);
    }

    void _rangeUpdate(int rt, int rtL, int rtR, int L, int R, const Tag &v) {
        if(rtL>=R || rtR<=L) return;
        if(rtL>=L && rtR<=R){ addTag(rt,v); return; }
        if(rtR-rtL>1) push_down(rt);
        _rangeUpdate(ls,rtL,mid,L,R,v);
        _rangeUpdate(rs,mid,rtR,L,R,v);
        if(rtR-rtL>1) push_up(rt);
    }

    Info _rangeQuery(int rt,int rtL,int rtR,int L,int R) {
        if(L>=rtR || R<=rtL) return Info();
        if(L<=rtL && R>=rtR) return info[rt];
        push_down(rt);
        return _rangeQuery(ls,rtL,mid,L,R)+_rangeQuery(rs,mid,rtR,L,R);
    }

public:
    int n;
    SegmentTree(int _n): n(_n), info(4<<std::__lg(_n)), tag(4<<std::__lg(_n)) {}
    SegmentTree(const std::vector<Info> &_init): SegmentTree(_init.size()) {
        auto build=[&](auto self,int rt,int rtL,int rtR){
            if(rtR-rtL==1){ info[rt]=_init[rtL]; return; }
            self(self,ls,rtL,mid);
            self(self,rs,mid,rtR);
            push_up(rt);
        };
        build(build,1,0,n);
    }

    void pointUpdate(int pos, const Info &v){ _pointUpdate(1,0,n,pos,v); }
    void rangeUpdate(int L, int R, const Tag &v){ _rangeUpdate(1,0,n,L,R,v); }
    Info rangeQuery(int L, int R){ return _rangeQuery(1,0,n,L,R); }
};

// 下面的代码维护区间最大值，支持区间加、区间赋值
const long long NOT_EXIST = -1;

struct Tag {
    long long plus,chg;
    Tag(): plus(0), chg(NOT_EXIST){}
    Tag(long long _plus,long long _chg): plus(_plus), chg(_chg){}
    void apply(Tag t) {
        if(t.chg!=NOT_EXIST){ plus = 0; chg = t.chg; }
        plus += t.plus;
    }
};

int MOD;

struct Info {
    long long Max = NOT_EXIST;
    Info(){}
    void apply(Tag t) {
        if(t.chg!=NOT_EXIST) Max = t.chg;
        Max += t.plus;
    }
};

inline Info operator+(const Info &a, const Info &b) {
    Info c;
    c.Max = std::max(a.Max,b.Max);
    return c;
}

struct Graph {
    size_t n;
    vector<vector<int>> adj;
    Graph(size_t _n): n(_n), adj(_n+1) {};
    constexpr void add_edge(int u, int v){ adj[u].emplace_back(v); }
};

// 以下为树剖

class HPD { // 树链剖分
private:
    struct inHPD{ int dep, dfn, siz, son, top, pre, val; };
    void dfs0(int u, int p) {
        info[u].siz = 1;
        info[u].dep = info[info[u].pre = p].dep+1;
        for(auto &v:G->adj[u]){
            if(v==p) continue;
            dfs0(v, u);
            info[u].siz += info[v].siz;
            if(!info[u].son || info[info[u].son].siz>info[v].siz) info[u].son = v;
        }
    }
    
    size_t n, tot;
    vector<Info> newArr;
    void dfs1(int u, int top) {
        newArr[tot] = Info{ };
        info[u].dfn = tot++;
        info[u].top = top;
        if(!info[u].son) return;
        dfs1(info[u].son, top);
        for(auto &v:G->adj[u]){
            if(v==info[u].pre || v==info[u].son) continue;
            dfs1(v, v);
        }
    }
    
public:
    vector<inHPD> info;
    Graph *G;
    SegmentTree<Info, Tag> ST;
    HPD(Graph *gra): n(gra->n), G(gra), info(gra->n+1), newArr(gra->n+1) {
        dfs0(1, 0);
        tot = 0;
        dfs1(1, 1);
        ST = SegmentTree<Info, Tag>(newArr);
    }
    
    int getLCA(int u, int v) {
        while(info[u].top != info[v].top){
            if(info[info[u].top].dep < info[info[v].top].dep) std::swap(u, v);
            u = info[info[u].top].pre;
        }
        if(info[u].dep > info[v].dep) std::swap(u, v); // 使得u节点所在树深度更浅
        return u;
    }

    void path_rangeUpdate(int u, int v, const Tag &w) { // u->v +w
        while(info[u].top != info[v].top){
            if(info[info[u].top].dep < info[info[v].top].dep) std::swap(u, v);
            ST.rangeUpdate(info[info[u].top].dfn, info[u].dfn+1, w);
            u = info[info[u].top].pre;
        }
        if(info[u].dep > info[v].dep) std::swap(u, v); // 使得u节点所在树深度更浅
        ST.rangeUpdate(info[u].dfn, info[v].dfn+1, w);
    };
    
    void tree_rangeUpdate(int rt, const Tag &w) {
        ST.rangeUpdate(info[rt].dfn, info[rt].dfn+info[rt].siz, w);
    }

    Info path_rangeQuery(int u, int v) {
        Info res{};
        while(info[u].top != info[v].top){
            if(info[info[u].top].dep < info[info[v].top].dep) std::swap(u, v);
            res = res+ST.query(info[info[u].top].dfn, info[u].dfn+1);
            u = info[info[u].top].pre;
        }
        if(info[u].dep > info[v].dep) std::swap(u, v);
        res = res+ST.query(info[u].dfn, info[v].dfn+1);
        return res;
    }
    
    Info tree_rangeQuery(int rt) {
        return ST.rangeQuery(info[rt].dfn, info[rt].dfn+info[rt].siz);
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    cin>>n>>m>>rt>>MOD;
    adj.resize(n+1); aa.resize(n+1); new_aa.resize(n+1);
    for(int i=1;i<=n;++i) cin>>aa[i].val;
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        adj[u].emplace_back(v); adj[v].emplace_back(u);
    }
   
    dfs1(rt,0);
    dfs2(rt,rt);

    ST=SegmentTree<int>(new_aa,MOD);

    while(m--){
        int opt,u,v,w; cin>>opt;
        switch(opt){
            case 1: cin>>u>>v>>w; add_range(u,v,w); break;
            case 2: cin>>u>>v; cout<<query_range(u,v)<<endl; break;
            case 3: cin>>u>>w; add_tree(u,w); break;
            case 4: cin>>u; cout<<query_tree(u)<<endl; break;        
        }
    }
    return 0;
}