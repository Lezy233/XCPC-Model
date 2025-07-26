/**
 * @warning 注意如果原图不保证联通，那么得出来的 kruskal 重构树也不连通
 */
#include <bits/stdc++.h>

std::vector<int> Log2;

template <class T>
class SparseTable { // 使用ST表前请自备Log2[]数组
private:
    int n;
    std::vector<std::vector<T>> info;
    std::function<T(const T&, const T&)> cmp; // 比较函数
    constexpr T check(const T &lhs, const T &rhs) {
        return cmp(lhs,rhs)? lhs:rhs;
    }
public:
    // vec 1-indexed
    SparseTable(const std::vector<T> &vec, std::function<T(const T&, const T&)> compare = std::greater<T>())
    : n(vec.size()-1), cmp(compare) {
        if(Log2.size()<=n){
            int i = std::max(int(Log2.size()), 2);
            Log2.resize(n+1);
            Log2[1] = 0;
            for(; i<=n; ++i) Log2[i] = Log2[i>>1]+1;
        }
        info.resize(n+1, std::vector<T>(Log2[n]+1));
        for(int i=1; i<=n; ++i) info[i][0] = vec[i];
        for(int j=1; j<=Log2[n]; ++j)
            for(int i=1; i-1+(1<<j)<=n; ++i)
                info[i][j] = check(info[i][j-1], info[i+(1<<j-1)][j-1]);
    }
    T find(int L, int R) {
        int len = Log2[R-L+1];
        return check(info[L][len], info[R+1-(1<<len)][len]);
    }
};

int32_t main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q; std::cin>>n>>m>>q;
    std::vector<std::array<int,3>> edges(m);
    for(auto &[w,u,v]:edges) std::cin>>u>>v>>w;
    std::ranges::sort(edges);

    std::vector<int> Set(n*2);
    std::iota(Set.begin(), Set.end(), 0);
    auto find = [&Set](auto self, int x)->int { return Set[x]==x? x : Set[x] = self(self, Set[x]); };

    std::vector<int> val;
    std::vector<std::vector<int>> adj(n+1);
    for(auto [w,u,v]:edges) {
        u = find(find, u), v = find(find, v);
        if(u == v) continue;
        int p = adj.size();
        adj.emplace_back();
        Set[u] = Set[v] = p;
        adj[p].emplace_back(u), adj[p].emplace_back(v);
        if(val.size() <= p) val.resize(p+1);
        val[p] = w;

        if(adj.size() == n*2) break;
    }
    
    std::vector<int> A(n*2-1), dfn(n*2);
    int tot = 0;
    auto dfs0 = [&](auto self, int u, int p=0)->void {
        A[tot] = p;
        dfn[u] = ++tot;
        for(auto &v:adj[u]) self(self, v, u);
    };
    dfs0(dfs0, n*2-1);
    
    SparseTable<int> ST(A,
        [&dfn](const int &lhs, const int &rhs) {
            return dfn[lhs] < dfn[rhs];
        }
    );
    
    auto LCA = [&](int u, int v) {
        if(u == v) return u;
        if(dfn[u] > dfn[v]) std::swap(u, v);
        return ST.find(dfn[u], dfn[v]-1);
    };
    
    while(q--) {
        int u,v; std::cin>>u>>v;
        int lca = LCA(u, v);
        std::cout<<val[lca]<<"\n";
    }
    return 0;
}