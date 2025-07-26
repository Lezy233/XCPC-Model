/**
 * @brief   MinCostFlow 最小费用最大流
 * @note    使用 Dinic 算法实现
 * @note    如果用类似于二分图匹配，请使用本算法
 */
// P3381
#include <bits/stdc++.h>

template <typename T>
class MCF_Graph {
private:
    struct _Edge {
        int to;
        T cap, cost;
        _Edge(int _to, T _cap, T _cost): to(_to), cap(_cap), cost(_cost) {}
    };
    
    const int n;
    std::vector<_Edge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<int> cur;
    std::vector<T> dis;
    std::vector<bool> inQue;
    T minCost;

    bool SPFA(int s, int t) {
        dis.assign(n, std::numeric_limits<T>::max());
        std::queue<int> que;
        dis[s] = 0, inQue[s] = 1;
        que.emplace(s);
        while(que.size()) {
            const int u = que.front(); que.pop();
            inQue[u] = 0;
            cur[u] = 0;
            for(int i=0; i<adj[u].size(); ++i) {
                auto &[v,cp,ct] = edges[adj[u][i]];
                if(cp && dis[v] > dis[u]+ct) {
                    dis[v] = dis[u] + ct;
                    if(!inQue[v]) { que.emplace(v); inQue[v] = 1; }
                }
            }
        }
        return dis[t] != std::numeric_limits<T>::max();
    }
    
    T dfs(int u, int t, T flow) {
        if(u == t || flow <= 0) return flow;
        inQue[u] = 1;
        auto remain = flow;
        for(int &i=cur[u]; i<adj[u].size(); ++i) {
            const int j = adj[u][i];
            const auto &[v,cp,ct] = edges[j];
            if(!inQue[v] && cp > 0 && dis[v] == dis[u]+ct) {
                auto mxflow = dfs(v, t, std::min(remain, cp));
                if(mxflow>0) {
                    minCost += mxflow * ct;
                    remain -= mxflow;
                    edges[j].cap -= mxflow;
                    edges[j^1].cap += mxflow;
                }
            }
        }
        inQue[u] = 0;
        return flow - remain;
    }

public:
    MCF_Graph(size_t _n): n(_n), adj(_n), cur(_n), inQue(_n) {}
    
    void addEdge(int u, int v, T cost = 0, T cap = std::numeric_limits<T>::max()) {
        adj[u].emplace_back(edges.size());
        edges.emplace_back(v, cap, cost);
        adj[v].emplace_back(edges.size());
        edges.emplace_back(u, 0, -cost);
    }
    /// @return 
    // first: maxFlow
    // second: minCost
    std::pair<T, T> getFlow(int s, int t) {
        T maxFlow = 0;
        minCost = 0;
        while(SPFA(s, t)) {
            T ans;
            do {
                ans = dfs(s, t, std::numeric_limits<T>::max());
                maxFlow += ans;
            } while(ans > 0);
        }
        return {maxFlow, minCost};
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,S,T; std::cin>>n>>m>>S>>T;
    MCF_Graph<int> MF(n+1);
    while(m--) {
        int u,v,w,c; std::cin>>u>>v>>w>>c;
        MF.addEdge(u, v, c, w);
    }
    auto [maxFlow, minCost] = MF.getFlow(S, T);
    std::cout<<maxFlow<<" "<<minCost<<"\n";
    return 0;
}