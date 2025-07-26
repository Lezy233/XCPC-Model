/**
 * @brief   Virtual Tree  每次询问的节点有限，我们只需要根据所给的节点建立虚树，然后直接树上DP即可
 */
// P2495
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
    int n; cin>>n;
    vector<vector<PII>>adj(n+1);
    for(int i=1;i<n;++i){
        int u,v,w; cin>>u>>v>>w;
        adj[u].emplace_back(v,w); adj[v].emplace_back(u,w);
    }

    int tot=0;
    vector<int>dep(n+1), dfn(n+1), minDis(n+1,1e9);
    vector<array<int,20>>fa(n+1);
    auto dfs0=[&](auto self,int u,int p)->void{
        dep[u]=dep[p]+1;
        dfn[u]=++tot;
        fa[u][0]=p;
        for(int i=1;(1<<i)<=dep[u];++i) fa[u][i]=fa[fa[u][i-1]][i-1];
        for(auto &[v,w]:adj[u]) if(v!=p){
            minDis[v]=std::min(minDis[u],w);
            self(self,v,u);
        }
    };
    dfs0(dfs0,1,0);

    auto lca=[&](int u,int v)->int{
        if(dep[u]<dep[v]) std::swap(u,v);
        for(int i=19;~i;--i)
            if(dep[u]-(1<<i)>=dep[v]) u=fa[u][i];
        if(u==v) return v;
        for(int i=19;~i;--i)
            if(fa[u][i]!=fa[v][i]) u=fa[u][i], v=fa[v][i];
        return fa[u][0];
    };

    vector<vector<PII>>virTree(n+1);
    int m; cin>>m;
    while(m--){
        int k; cin>>k;
        vector<int>ild(k); // islands
        for(auto &i:ild) cin>>i;
        std::set<int>st(ALL(ild));
        std::ranges::sort(ild,[&](const int&x,const int&y){
            return dfn[x]<dfn[y];
        });
        for(int i=1;i<k;++i) ild.emplace_back(lca(ild[i-1],ild[i]));
        ild.emplace_back(1);
        std::ranges::sort(ild,[&](const int&x,const int&y){
            return dfn[x]<dfn[y]; 
        });
        ild.erase(std::unique(ALL(ild)),ild.end());

        vector<int>used;
        for(int i=1;i<ild.size();++i){
            int u=lca(ild[i-1],ild[i]); // 此处的LCA只是为了搞清楚该节点的父节点
            virTree[u].emplace_back(ild[i],minDis[ild[i]]);
            used.emplace_back(u);
        }

        auto dfs=[&](auto self,int u)->ll{
            ll ans=0;
            for(auto &[v,w]:virTree[u]){
                if(st.contains(v)) ans+=w;
                else ans+=std::min(self(self,v),ll(w));
            }
            return ans;
        };
        cout<<dfs(dfs,1)<<endl;        
        for(auto &i:used) virTree[i].clear();
    }
    return 0;
}



/* 另外一种写法，使用单调栈维护虚树
    vector<vector<PII>>virTree(n+1);
    int m; cin>>m;
    while(m--){
        int k; cin>>k;
        vector<int>ild(k); // islands
        for(auto &i:ild) cin>>i;
        std::ranges::sort(ild,[&](const int&x,const int&y){
            return dfn[x]<dfn[y];
        });
        std::set<int>key(ALL(ild));
        vector<int>st={1};
        vector<int>used;
        for(auto &i:ild){
            int u=lca(i,st.back());
            while(dfn[st.back()]>dfn[u]){
                if(dfn[st[st.size()-2]]>dfn[u]) virTree[st[st.size()-2]].emplace_back(st.back(),minDis[st.back()]);
                else virTree[u].emplace_back(st.back(),minDis[st.back()]);
                st.pop_back();
                used.emplace_back(st.back());
            }
            if(u!=st.back()) st.emplace_back(u);
            st.emplace_back(i);
        }
        for(int i=0;i<st.size()-1;++i){
            virTree[st[i]].emplace_back(st[i+1],minDis[st[i+1]]);
            used.emplace_back(st[i]);
        }        

        auto dfs=[&](auto self,int u)->ll{
            ll ans=0;
            for(auto &[v,w]:virTree[u]){
                if(key.contains(v)) ans+=w;
                else ans+=std::min(self(self,v),ll(w));
            }
            return ans;
        };
        cout<<dfs(dfs,1)<<endl;        
        for(auto &i:used) virTree[i].clear();
    }
 */