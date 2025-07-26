// P5782 AC
#include <bits/stdc++.h>
#define endl "\n"
#define ALL(x) x.begin(),x.end()

class TwoSAT {
private:
    int n;
    std::vector<bool> ans;
    std::vector<std::vector<int>> adj;
public:
    TwoSAT(size_t _n): n(_n), adj(_n<<1), ans(_n) {}
    
    void add_clause(int u, bool f, int v, bool g) { // u<<1|f 与 v<<1|g 冲突
        adj[u<<1|f].emplace_back(v<<1|1-g);
        adj[v<<1|g].emplace_back(u<<1|1-f);
    }
    
    bool satisfiable() {
        std::vector<int> stk;
        std::vector<int> id(n<<1, -1), dfn(n<<1, -1), low(n<<1, -1);
        int cnt = 0, tot = 0;
        auto tarjan = [&](auto self, int u)->void {
            stk.emplace_back(u);
            dfn[u] = low[u] = tot++;
            for(auto &v:adj[u]) {
                if(dfn[v] == -1) {
                    self(self, v);
                    low[u] = std::min(low[u], low[v]);
                } else if(id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if(dfn[u] == low[u]) {
                int t;
                do {
                    t = stk.back(); stk.pop_back();
                    id[t] = cnt;
                } while(t != u);
                ++cnt;
            }
        };
        
        for(int i=0; i<n*2; ++i) if(dfn[i] == -1) tarjan(tarjan, i);
        for(int i=0; i<n; ++i) {
            if(id[i<<1] == id[i<<1|1]) return false;
            ans[i] = id[i<<1] > id[i<<1|1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};

void solve()
{
    int n,m; std::cin>>n>>m;
    TwoSAT twosat(n);
    while(m--) {
        int u,v; std::cin>>u>>v; --u, --v;
        twosat.add_clause(u>>1, u&1, v>>1, v&1);
    }
    if(twosat.satisfiable() == false) {
        std::cout<<"NIE\n"; return;
    }
    auto res = std::move(twosat.answer());
    for(int i=0; i<n; ++i) std::cout<<(i<<1|res[i])+1<<"\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    std::ifstream in("C++/in.txt");
    std::cin.rdbuf(in.rdbuf());
#endif
    int T = 1;
    // std::cin>>T;
    while(T--) solve();
    return 0;
}