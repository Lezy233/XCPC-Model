/**
 * @brief   Bipartite Graph  二分图
 *          二分图最大匹配
*/

// P3386
/**
 * @note    Augmenting Path Algorithm  增广路算法
*/
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"
#define ALL(x) x.begin(),x.end()
typedef long long ll;
typedef std::pair<int,int> PII;
typedef std::tuple<int,int,int> T3I;

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,e; cin>>n>>m>>e;
    vector<vector<int>>adj(n+1);
    while(e--){
        int u,v; cin>>u>>v;
        adj[--u].emplace_back(--v);
    }

    vector<int> vis(m,0);
    vector<int> ano(m,-1);
    auto match = [&](auto self, int u)->bool {
        for(auto &v:adj[u]){
            if(vis[v]++) continue;
            if(ano[v]==-1||self(self,ano[v])){
                ano[v]=u;
                return true;
            }
        }
        return false;
    };
    int res=0;
    for(int i=0;i<n;++i){
        std::ranges::fill(vis,0);
        res += match(match,i);
    }
    cout<<res<<endl;
    return 0;
}