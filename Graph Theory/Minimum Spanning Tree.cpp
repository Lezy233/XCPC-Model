#include <bits/stdc++.h>
using namespace std;
//Minimum spanning tree,MST
const int N=2e5+2;
//洛谷P3366
//Kruskal
/*
struct node{
    int from,to,w;
}edge[N];
bool cmp(node a,node b){
    return a.w<b.w;
}
int s[N]={0};
void init_set(int n){
    for(int i=1;i<=n;i++)
        s[i]=i;
}
int find_set(int x){
    if(x!=s[x]) s[x]=find_set(s[x]);//路径压缩
    return s[x];
}
void merge_set(int x,int y){
    x=find_set(x);y=find_set(y);
    if(x!=y)s[x]=s[y];
}
int cnt=0;
int main()
{
    int n,m;cin>>n>>m;
    init_set(n);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&edge[i].from,&edge[i].to,&edge[i].w);
    sort(edge+1,edge+1+m,cmp);
    long long ans=0;
    for(int i=1;i<=m;i++){
        if(find_set(edge[i].from)!=find_set(edge[i].to)){
            ans+=edge[i].w;
            merge_set(edge[i].from,edge[i].to);
            cnt++;
            if(cnt==n-1) break;
        }
    }
    if(cnt==n-1) cout<<ans<<endl;
    else cout<<"orz"<<endl;
    return 0;
}
*/