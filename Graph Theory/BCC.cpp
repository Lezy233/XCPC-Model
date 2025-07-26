/**
 * @brief BCC Biconnected Component 双连通分量
 *        Vertex Biconnected Component 点双连通分量
 */

#include <bits/stdc++.h>

struct Graph {
    size_t n;
    std::vector<std::vector<int>> adj;
    Graph(size_t n_): n(n_), adj(n_) {}
    void addEdge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
};

std::vector<std::vector<int>> getBCC(const Graph &G) {
    const auto &[n, adj] = G;

    int tot = 0;
    std::vector<std::vector<int>> vSet; // 点双集合
    std::vector<int> dfn(n), low(n);
    std::stack<int> stk;
    auto tarjan = [&](auto self, int u, int p = -1)->void {
        dfn[u] = low[u] = ++tot;
        stk.emplace(u);
        int cntSon = 0;
        for(auto v:adj[u]) if(v != p) {
            ++cntSon;
            if(!dfn[v]) {
                self(self, v, u);
                low[u] = std::min(low[u], low[v]);
                if(low[v] >= dfn[u]) {
                    vSet.emplace_back(1, u);
                    int t;
                    do {
                        t = stk.top(); stk.pop();
                        vSet.back().emplace_back(t);
                    } while(t != v);
                }
            }
            low[u] = std::min(low[u], dfn[v]);
        }
        
        if(cntSon == 0 && p == -1)
            vSet.emplace_back(1, u);
    };
    
    for(int i = 0; i < n; ++i) if(!dfn[i]) tarjan(tarjan, i);
    return vSet;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; std::cin >> n >> m;
    
    Graph G(n);
    while(m--) {
        int u,v; std::cin >> u >> v; --u, --v;
        if(u != v) G.addEdge(u, v);
    }
    
    auto vdcc = std::move(getBCC(G));
    std::cout << vdcc.size() << "\n";
    for(auto &i:vdcc) {
        std::cout << i.size() << " ";
        for(auto &j:i) std::cout << j+1 << " ";
        std::cout << "\n";
    }
    return 0;
}