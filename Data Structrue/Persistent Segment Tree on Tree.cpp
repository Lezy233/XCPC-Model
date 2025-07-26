/**
 * @brief   Persistent Segment Tree on Tree  树上可持久化线段树
 */

// P2633
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"
#define ALL(x) x.begin(),x.end()
typedef long long ll;
typedef std::pair<int,int> PII;
typedef std::tuple<int,int,int> T3I;

constexpr int N=1e5+3;

int root[N], tot=0;
struct Info{
    int L,R,cnt;
}info[N<<5];

#define ls(rt) info[rt].L
#define rs(rt) info[rt].R
#define mid (rtL+rtR>>1)
int update(int pre,int rtL,int rtR,int x) {
    int rt=++tot;
    info[rt]=info[pre];
    ++info[rt].cnt;
    if(rtL<rtR){
        if(x<=mid) ls(rt)=update(ls(pre),rtL,mid,x);
        else       rs(rt)=update(rs(pre),mid+1,rtR,x);
    }
    return rt;
}

int query(int L1,int R1,int L2,int R2,int rtL,int rtR,int k) {
    if(rtL==rtR) return rtL;
    int ls_cnt=info[ls(R1)].cnt-info[ls(L1)].cnt
              +info[ls(R2)].cnt-info[ls(L2)].cnt;
    if(k<=ls_cnt) return query(ls(L1),ls(R1),ls(L2),ls(R2),rtL,mid,k);
    else          return query(rs(L1),rs(R1),rs(L2),rs(R2),mid+1,rtR,k-ls_cnt);
}
#undef ls
#undef rs
#undef mid

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; cin>>n>>m;
    vector<int>val(n+1);
    for(int i=1;i<=n;++i) cin>>val[i];
    auto alls=val;
    std::ranges::sort(alls);
    alls.erase(std::unique(ALL(alls)),alls.end());
    std::map<int,int>mp;
    for(int i=1;i<alls.size();++i) mp[alls[i]]=i;

    vector<vector<int>>adj(n+1);
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        adj[u].emplace_back(v); adj[v].emplace_back(u);
    }

    vector<int>dep(n+1);
    vector<vector<int>>fa(n+1,vector<int>(18));
    auto dfs0=[&](auto self,int u,int p)->void{
        dep[u]=dep[fa[u][0]=p]+1;
        root[u]=update(root[p],1,mp.size(),mp[val[u]]);
        for(int i=1;(1U<<i)<=dep[u];++i) fa[u][i]=fa[fa[u][i-1]][i-1];
        for(auto &v:adj[u]) if(v!=p) self(self,v,u);
    };
    dfs0(dfs0,1,0);
    
    auto LCA=[&](int u,int v)->int{
        if(dep[u]<dep[v]) std::swap(u,v);
        for(int i=17;~i;--i) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
        if(u==v) return u;
        for(int i=17;~i;--i) if(fa[u][i]!=fa[v][i]) u=fa[u][i], v=fa[v][i];
        return fa[u][0];
    };

    int lastAns=0;
    while(m--){
        int u,v,k; cin>>u>>v>>k; u^=lastAns;
        int lca=LCA(u,v);
        cout<<(lastAns=alls[query(root[fa[lca][0]],root[u],root[lca],root[v],1,mp.size(),k)])<<endl;                        
    }
    return 0;
}