/**
 * @brief   CDQ Divide_and_Conquer  CDQ分治
*/
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef std::tuple<int,int,int> T3I;

struct Node{
    int a,b,c,cnt,ans;
    int isL;
};

using It=std::vector<Node>::iterator;

void cdq2(It L, It R) { // [L,R)
    if(R-L==1) return;
    auto mid=L+(R-L)/2;
    cdq2(L,mid); cdq2(mid,R);

    vector<Node>tmp(R-L);
    
    auto i=L; auto k=tmp.begin();
    int cnt=0;
    for(auto j=mid;j!=R;){
        for(;i!=mid&&i->c<=j->c;){
            cnt+=i->cnt*i->isL;
            *k++=*i++;
        }
        j->ans+=cnt*!j->isL;
        *k++=*j++;
    }
    while(i!=mid) *k++=*i++;
    for(k=tmp.begin();L!=R;) *L++=*k++;
}

void cdq1(It L, It R) { // [L,R)
    if(R-L==1) return;
    auto mid=L+(R-L)/2;
    cdq1(L,mid); cdq1(mid,R);
    std::sort(L,R,[](const Node&x,const Node&y){
        return x.a<y.a || x.a==y.a&&x.b<y.b || x.a==y.a&&x.b==y.b&&x.c<y.c;
    });
    for(auto i=L;i!=mid;++i) i->isL=1;
    for(auto i=mid;i!=R;++i) i->isL=0;
    std::stable_sort(L,R,[](const Node &x,const Node &y){
        return x.b<y.b;
    });
    cdq2(L,R);
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k; cin>>n>>k;
    vector<Node>aa;
    std::map<T3I,int>mp;
    for(int i=0;i<n;++i){
        int a,b,c; cin>>a>>b>>c;
        ++mp[{a,b,c}];
    }
    for(auto &[key,cnt]:mp){
        auto &[a,b,c]=key;
        aa.emplace_back(a,b,c,cnt,0);
    }

    vector<int>res(n,0);
    cdq1(aa.begin(),aa.end());

    for(auto &[a,b,c,cnt,ans,_]:aa) res[ans+cnt-1]+=cnt;
    for(auto &i:res) cout<<i<<endl;
    return 0;
}