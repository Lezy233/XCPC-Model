#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"
#define ALL(x) x.begin(), x.end()
using ll = long long;
using PII = std::pair<int,int>;
using T3I = std::tuple<int,int,int>;

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

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,s; cin>>n>>m>>s;
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; ++i) {
        int u,v; cin>>u>>v;
        adj[u].emplace_back(v), adj[v].emplace_back(u);
    }
    
    vector<int> A(n), dfn(n+1);
    int tot = 0;
    auto dfs0 = [&](auto self, int u, int p=0)->void {
        A[tot] = p;
        dfn[u] = ++tot;
        for(auto v:adj[u]) if(v != p) self(self, v, u);
    };
    dfs0(dfs0, s);
    
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
    
    while(m--) {
        int u,v; cin>>u>>v;
        cout << LCA(u, v) << endl;
    }
    return 0;
}