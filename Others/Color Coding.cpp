// HDU-6664 AC
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"
#define ALL(x) x.begin(),x.end()
using ll = long long;
using PII = std::pair<int,int>;
using T3I = std::tuple<int,int,int>;

std::mt19937 rng(std::chrono::steady_clock().now().time_since_epoch().count());
constexpr int INF = 1e9;

template <class T>
constexpr void cmax(T &lhs, const T &rhs){ if(lhs<rhs) lhs = rhs; }

constexpr int N = 1e4;
array<array<int,N>, 1U<<6> dp;
void solve()
{
    int n,m,k; cin>>n>>m>>k;
    vector<vector<PII>> adj(n);
    while(m--){
        int u,v,w; cin>>u>>v>>w; --u, --v;
        adj[u].emplace_back(v,w); adj[v].emplace_back(u,w);
    }
    vector<int> color(n);
    int res = 0;
    unsigned msk = 1U<<k;
    // vector<vector<ll>> dp(msk, vector<ll>(n,-INF));
    for(int o=300; o; --o){
        for(auto &i:color) i = rng()%k;
        for(int i=0; i<n; ++i){
            for(unsigned j=0; j<msk; ++j) dp[j][i] = -INF;
            dp[1U<<color[i]][i] = 0;
        }

        for(unsigned s=1; s<msk; ++s){
            for(int u=0; u<n; ++u){
                if(!(s&1U<<color[u])) continue;
                for(auto &[v,w]:adj[u])
                    cmax(dp[s][u], dp[s^1U<<color[u]][v]+w);
            }
        }
        for(int i=0; i<n; ++i) cmax(res, dp[msk-1][i]);
        // cmax(res, std::ranges::max(dp[msk-1]));
    }
    if(res) cout<<res<<endl;
    else cout<<"impossible\n";
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    std::ifstream in("C++/in.txt");
    std::cin.rdbuf(in.rdbuf());
#endif
    int T; cin>>T;
    while(T--) solve();
    return 0;
}