// P4779
#include<bits/stdc++.h>
using namespace std;
//const int N=8,M=16;
const int N=1e5+2,M=2e5+5;
const int INF=0x3f3f3f3f;
int n,m,s;
struct edge{
    int from,to,w;
    edge(int a,int b,int c){from=a; to=b; w=c;}
};
vector<edge>e[M];
struct node{
    int id,dis;
    node(int a,int b){id=a; dis=b;}
    bool operator < (const node &c) const 
    {return dis>c.dis;}
};
int dis[N]={0}; //记录所有节点到起点的距离
bool vis[N]={false}; //记录当前节点是否找到最短距离
void dijkstra(){
    for(int i=1;i<=n;++i){dis[i]=INF; vis[i]=false;}
    dis[s]=0;
    priority_queue<node>pq;
    pq.push(node(s,dis[s]));
    while(pq.size()){
        node now=pq.top(); pq.pop(); //now为当前的点
        if(vis[now.id]) continue;
        vis[now.id]=true;
        for(int i=0;i<e[now.id].size();++i){
            edge temp=e[now.id][i]; //temp为当前的边
            if(vis[temp.to]) continue;
            if(dis[temp.to]>temp.w+now.dis){
                dis[temp.to]=temp.w+now.dis;
                pq.push(node(temp.to,dis[temp.to]));
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    int u,v,w; cin>>n>>m>>s;
    for(int i=1;i<=n;++i) e[i].clear();
    while(m--){
        cin>>u>>v>>w;
        e[u].push_back(edge(u,v,w));
    }
    dijkstra();
    for(int i=1;i<=n;++i)
        printf("%d ",dis[i]);
    return 0;
}