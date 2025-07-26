// P3367
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; cin>>n>>m;
    
    std::vector<int>S(n+1);
    std::iota(S.begin(),S.end(),0);
    auto findSet=[&](auto self,int x)->int{ return x==S[x]? x:S[x]=self(self,S[x]); };

    while(m--){
        int opt,u,v; cin>>opt>>u>>v;
        u=findSet(findSet,u), v=findSet(findSet,v);
        if(opt==1) S[u]=v;
        else cout<<(u==v? "Y\n":"N\n");
    }
    return 0;
}