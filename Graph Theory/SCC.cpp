/**
 * @brief   Strongly Connected Components, SCC, 强连通分量
 * @note    个人感觉Kosaraju的做法好理解好敲
*/

#include <bits/stdc++.h>

/**
 * @note    Tarjan做法
*/
void Tarjan() {
    int n,m; std::cin >> n >> m;
    std::vector<std::vector<int>> adj(n+1);
    while(m--) {
        int u,v; std::cin >> u >> v;
        adj[u].emplace_back(v);
    }

    std::vector<short> in_Stack(n+1);
    std::vector<int> dfn(n+1), low(n+1), belong(n+1); // belong[i] 表示点i属于哪一个SCC
    std::stack<int> st;
    int res = 0, cnt = 0, tot = 0; // cnt: 强连通分量数量; tot: dfn序
    auto tarjan = [&](auto self,int u)->void {
        in_Stack[u] = 1;
        dfn[u] = low[u] = ++tot;
        st.emplace(u);
        for(auto &v:adj[u]) {
            if(!dfn[v]) {
                self(self, v);
                low[u] = std::min(low[u], low[v]);
            } else if(in_Stack[v]) {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
        if(dfn[u] == low[u]) {
            int t, count = 0;
            ++cnt;
            do {
                t = st.top(); st.pop();
                in_Stack[t] = 0;
                belong[t] = cnt;
                ++count;
            } while(t != u);
            res += count > 1;
        }
    };
    for(int i=1; i<=n; ++i) if(!dfn[i]) tarjan(tarjan, i);
    std::cout << res << "\n";
}

/**
 * @note    Kosaraju做法
*/
void Kosaraju() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; std::cin>>n>>m;
    std::vector<std::vector<int>>adj(n+1), reAdj(n+1);
    while(m--){
        int u,v; std::cin>>u>>v;
        adj[u].emplace_back(v);
        reAdj[v].emplace_back(u);
    }

    std::vector<int>dfn;
    std::vector<bool>vis(n+1);
    auto dfs0=[&](auto self,int u)->void{
        vis[u]=true;
        for(auto &v:adj[u]) if(!vis[v]) self(self,v);
        dfn.emplace_back(u);
    };

    int cnt=0; // SCC数量
    std::vector<int>belong(n+1);
    auto dfs1=[&](auto self,int u)->void{
        belong[u]=cnt;
        for(auto &v:reAdj[u]) if(!belong[v]) self(self,v);
    };

    for(int i=1;i<=n;++i) if(!vis[i]) dfs0(dfs0,i);
    for(auto i:std::views::reverse(dfn)){
        if(belong[i]) continue;
        ++cnt;
        dfs1(dfs1,i);
    }
}