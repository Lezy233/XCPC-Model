/**
 * @brief   倍增求 LCA
 */
#include <bits/stdc++.h>

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; std::cin >> n >> m;
    std::vector<std::vector<int>> adj(n+1);
    for(int i=1;i<n;++i){
        int u,v; std::cin >> u >> v;
        adj[u].emplace_back(v); adj[v].emplace_back(u);
    }

    std::vector<int> dep(n+1);
    std::vector<std::array<int,20>> fa(n+1);
    auto dfs0 = [&](auto self, int u, int p = 0)->void {
        dep[u] = dep[p] + 1;
        fa[u][0] = p;
        for(int i=1; (1<<i)<=dep[u]; ++i)
            fa[u][i] = fa[fa[u][i-1]][i-1];
        for(auto v:adj[u]) if(v!=p) self(self, v, u);
    };
    dfs0(dfs0,1);

    auto lca = [&](int u, int v)->int {
        if(dep[u] < dep[v]) std::swap(u, v);
        for(int i=19; ~i; --i) if(dep[fa[u][i]] >= dep[v]) u = fa[u][i];
        if(u == v) return v;
        for(int i=19; ~i; --i)
            if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
        return fa[u][0];
    };
    return 0;
}