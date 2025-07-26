#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
//P3371
const ll INF=0x3f3f3f3f3f3f3f3f;
//const ll INF=2147483647;
const int N=5e5+3;
//SPFA
struct edge{
    int to;ll w;
    edge(int tt,ll ww){to=tt;w=ww;}
};
ll dist[N]={0};
bool in_q[N]={false};//in_q[k]表示第k个点是否在队列中
vector<edge>e[N];
void spfa(int s){
    memset(dist,0x3f,sizeof(dist));
    dist[s]=0;
    queue<int>q;
    q.push(s);
    in_q[s]=true;
    while(!q.empty()){
        int u=q.front(); q.pop();
        in_q[u]=false;//u已经不在队列中
        if(dist[u]==INF) continue;
        for(int i=0;i<e[u].size();i++){//遍历u的邻居
            int v=e[u][i].to;
            ll w=e[u][i].w;
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;//更新最短路径
                if(!in_q[v]){
                    q.push(v);
                    in_q[v]=true;
                }
            }
        }
    }
}
int main()
{
    int n,m,s;cin>>n>>m>>s;
    for(int i=1;i<=m;i++){
        int u,v;ll w;
        scanf("%d%d%lld",&u,&v,&w);
        e[u].push_back(edge(v,w));
    }
    spfa(s);
    for(int i=1;i<=n;i++){
        if(dist[i]==INF)printf("2147483647 ");
        else printf("%d ",dist[i]);
    }
    return 0;
}