#include <bits/stdc++.h>
using namespace std;
#define N 5001
int n,m;
int head[N]={0},cnt=0;
struct node{//链式前向星
    int to,nex,w;
}edge[N];//边集
void init(){//初始化
    for(int i=0;i<=n;i++)head[i]=-1;
    cnt=0;
}
void add(int u,int v){//加边，u起点，v终点
    edge[cnt].to=v;//终点
    edge[cnt].nex=head[u];//以u为起点上一条边的编号，也就是与这个边起点相同的上一条边的编号
    head[u]=cnt++;//更新以u为起点上一条边的编号
}
int main()
{
    init();
    int a,b;
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>a>>b;
        add(a,b);
    }
    for(int i=1;i<=n;i++){
        cout<<i<<endl;
        for(int j=head[i];j!=-1;j=edge[j].nex){//for中间也可以改为~j
            cout<<i<<" "<<edge[j].to<<" "<<edge[j].w<<endl;
        }
    }
    return 0;
}