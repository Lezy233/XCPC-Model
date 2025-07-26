/**
 * @brief   MaxFlow 最大流
 * @note    使用 Dinic 算法实现
 * @warning 注意如何使用的是 Dinic + 残量网络上逐层加点的做法的话，必须对 ans 进行累加
 *          同时建议另外开一个 vector 记录 bfs 时走过的点，在 dfs 结束时将 depth 清零
 * @note    最后面贴了 Dinic 算法复杂度
 */
// P3376
#include <bits/stdc++.h>

template <typename T>
class MaxFlow {
private:
    struct _Edge {
        int to;
        T cap;
        _Edge(int _to, T _cap): to(_to), cap(_cap) {}
    };
    
    int n;
    std::vector<_Edge> edges;
    std::vector<std::vector<int>> adj;
    std::vector<int> depth, cur; // cur 用于当前弧优化
    
    bool bfs(int s, int t) {
        depth.assign(n, 0);
        std::queue<int> q;
        depth[s] = 1;
        q.emplace(s);
        while(q.size()) {
            const int u = q.front(); q.pop();
            cur[u] = 0;
            for(int i=0; i<adj[u].size(); ++i) {
                auto &[v,c] = edges[adj[u][i]];
                if(c>0 && !depth[v]) {
                    depth[v] = depth[u]+1;
                    if(v==t) return true;
                    q.emplace(v);
                }
            }
        }
        return false;
    }
    
    T dfs(int u, int t, T flow) { // t 终点
        if(u==t || flow<=0) return flow;
        auto remain = flow;
        for(int &i=cur[u]; i<adj[u].size(); ++i) { // 此处当前弧优化
            const int j = adj[u][i];
            auto &[v,c] = edges[j];
            if(c > 0 && depth[v] == depth[u]+1) {
                auto mxflow = dfs(v, t, std::min(remain, c)); // mxflow: u->v
                if(mxflow<=0) { depth[v] = 0; continue; }
                remain -= mxflow;
                edges[j].cap -= mxflow;
                edges[j^1].cap += mxflow;
                if(remain == 0) return flow;
            }
        }
        return flow-remain;
    }
    
public:
    MaxFlow(size_t _n): n(_n), adj(_n), depth(_n), cur(_n) {}
    
    void addEdge(int u, int v, T c = std::numeric_limits<T>::max()) {
        adj[u].emplace_back(edges.size());
        edges.emplace_back(v, c);
        adj[v].emplace_back(edges.size());
        edges.emplace_back(u, 0);
    }
    
    T getFlow(int s, int t) {
        T ans = 0;
        while(bfs(s, t)) {
            // cur.assign(n,0); // 当前弧优化 Current Arc Optimization
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,s,t; std::cin>>n>>m>>s>>t; --s, --t;
    
    MaxFlow<long long> MF(n);
    while(m--) {
        int u,v,w; std::cin>>u>>v>>w; --u, --v;
        MF.addEdge(u, v, w);
    }
    std::cout<<MF.getFlow(s, t)<<"\n";
    return 0;
}

/*
    具体的复杂度证明查询 OI-wiki
    一般地, Dinic 单轮增广的时间复杂度为 O(|V||E|), 增广轮数为 O(|V|), 时间复杂度 O(|V|^2*|E|)
以下为特殊情况
    1. 网络 G 单位容量(Unit Capacity)
    此时单论增广复杂度 O(|E|), 增广轮数 O(|E|^1/2) or O(|V|^2/3)
    因此单位容量网络上 Dinic 算法时间复杂度 O(|E| min(|E|^1/2, |V|^2/3))
 */