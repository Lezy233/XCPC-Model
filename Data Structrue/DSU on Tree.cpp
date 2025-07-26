// DSU on tree 树上启发式合并
// DSU Disjoint Set Union 并查集

// Luogu U41492
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin>>n;
    vector<int>res(n+1,0);
    vector<vector<int>>adj(n+1);
    for(int i=1;i<n;++i){
        int u,v; cin>>u>>v;
        adj[u].emplace_back(v); adj[v].emplace_back(u);
    }
    vector<int>color(n+1);
    for(int i=1;i<=n;++i) cin>>color[i];

    vector<int>siz(n+1),son(n+1),L(n+1),R(n+1),Node(n+1);
    // L[i] i点的dfn序; R[i] i点为根的树的最大dfn序
    int cntDfn=0;

    auto dfs1=[&](auto self,int now,int pre)->void{
        siz[now]=1;
        L[now]=++cntDfn; Node[cntDfn]=now;
        for(auto &nxt:adj[now]){
            if(nxt==pre) continue;
            self(self,nxt,now);
            siz[now]+=siz[nxt];
            if(!son[now]||siz[nxt]>siz[son[now]]) son[now]=nxt;
        }
        R[now]=cntDfn;
    };
    dfs1(dfs1,1,0);

    int totColor=0;
    vector<int>cnt(n+1); // 颜色数

    auto add=[&](int x)->void{ if(cnt[color[x]]++==0) ++totColor; };
    auto del=[&](int x)->void{ if(--cnt[color[x]]==0) --totColor; };

    auto dfs2=[&](auto self,int now,int pre,bool keep)->void{
        for(auto &nxt:adj[now]) // 遍历轻儿子，结果最终不保留
            if(nxt!=pre&&nxt!=son[now]) self(self,nxt,now,false);
        if(son[now]) self(self,son[now],now,true);
        for(auto &nxt:adj[now]){
            if(nxt!=pre&&nxt!=son[now]){
                for(int i=L[nxt];i<=R[nxt];++i) add(Node[i]);
            }
        }
        add(now);
        res[now]=totColor;
        if(!keep){
            for(int i=L[now];i<=R[now];++i) del(Node[i]);
        }
    };
    dfs2(dfs2,1,0,true);

    int m; cin>>m;
    while(m--){
        int tt; cin>>tt;
        cout<<res[tt]<<endl;
    }
    return 0;
}