#include<bits/stdc++.h>
using namespace std;
//分块思想
const int N=4;
int main()
{
    int n; cin>>n;
    int st[N]={0},ed[N]={0};//分别表示每块的起点终点
    int block=sqrt(n);//每块中的数字个数
    int t=ceil((double)n/block);//块的数量
    for(int i=1;i<=t;i++){
        st[i]=(i-1)*block+1;
        ed[i]=i*block;
    }
    ed[t]=n;
    
}