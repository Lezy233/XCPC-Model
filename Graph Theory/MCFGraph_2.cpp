/**
 * @brief   MinCostFlow 最小费用最大流
 * @note    使用 Primal-Dual 原始对偶算法
 * @warning 如果需要实现二分图最大匹配，请使用 Dinic 算法
 */
// P3381
#include <bits/stdc++.h>

template <typename T>
class MCF_Graph {
private:
    using PTI = std::pair<T, int>;
    struct _Edge {
        int to;
        T cap, cost;
        _Edge(int _to, T _cap, T _cost): to(_to), cap(_cap), cost(_cost) {}
    };
    
    const int n;
    std::vector<_Edge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<T> h, dis;
    std::vector<int> pre;

    bool dijkstra(int s, int t) {
        dis.assign(n, std::numeric_limits<T>::max());
        pre.assign(n, -1);
        std::priority_queue<PTI, std::vector<PTI>, std::greater<PTI>> pq;
        dis[s] = 0;
        pq.emplace(0, s);
        while(!pq.empty()) {
            auto [uDis,u] = pq.top(); pq.pop();
            if(dis[u]<uDis) continue;
            for(auto &i:adj[u]) {
                auto &[v,cp,ct] = edges[i];
                if(cp>0 && dis[v]>uDis+h[u]-h[v]+ct) {
                    dis[v] = uDis+h[u]-h[v]+ct;
                    pre[v] = i;
                    pq.emplace(dis[v], v);
                }
            }
        }
        return dis[t] != std::numeric_limits<T>::max();
    }

public:
    MCF_Graph(size_t _n): n(_n), adj(_n) {}
    
    void addEdge(int u, int v, T cost = 0, T cap = std::numeric_limits<T>::max()) {
        adj[u].emplace_back(edges.size());
        edges.emplace_back(v, cap, cost);
        adj[v].emplace_back(edges.size());
        edges.emplace_back(u, 0, -cost);
    }
    // first: maxFlow
    // second: minCost
    std::pair<T, T> getFlow(int s, int t) {
        T maxFlow = 0, minCost = 0;
        h.assign(n, 0);
        while(dijkstra(s, t)) {
            for(int i=0; i<n; ++i) h[i] += dis[i];
            T aug = std::numeric_limits<T>::max();
            for(int i=t; i!=s; i=edges[pre[i]^1].to) aug = std::min(aug, edges[pre[i]].cap);
            for(int i=t; i!=s; i=edges[pre[i]^1].to) {
                edges[pre[i]].cap -= aug;
                edges[pre[i]^1].cap += aug;
            }
            maxFlow += aug;
            minCost += aug*h[t];
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