#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=101,Nmod=1e9+7;
ll n,k;
struct matrix{
    ll num[N][N];
    matrix(){
        memset(num,0,sizeof(num));
    }
    matrix(int i){
        for(int j=1;j<=n;++j) num[j][j]=i;
    }
};
matrix operator *(matrix a,matrix b){//重载运算符
    matrix ans;
    for(int k=1;k<=n;++k)
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j){
            ans.num[i][j]=(ans.num[i][j]+a.num[i][k]*b.num[k][j]%Nmod)%Nmod;
        }
    }
    return ans;
}
matrix binpow(matrix x,ll k){
    matrix ans=matrix(1);
    while(k){
        if(k&1) ans=ans*x;
        x=x*x;
        k>>=1;
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>k;
    matrix A;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin>>A.num[i][j];
    A=binpow(A,k);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=n;++j)
            cout<<A.num[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}