// Luogu B3637
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef std::pair<int,int> PII;
/* 
template <typename T>
struct max_FenwickTree
{
    int n;
    std::vector<T>a;
    int lowbit(int x){ return x&-x; }
  
    max_FenwickTree(int _n): n(_n), a(_n+1) {}
    max_FenwickTree(T *b,int _n): n(_n), a(_n+1) {}
  
    void init(int _n) {
        this->n=_n; a.resize(_n+1);
    }
  
    void change(int x,T v) {
        for(int i=x;i<=n;i+=lowbit(i)){
            a[i]=v;
            for(int j=1;j<lowbit(j);j<<=1)
                a[i]=std::max(a[i],a[i-j]);
        }
    }
    T rangeMax(int l,int r) {
        T ans=0;
        while(l<=r){
            ans=std::max(ans,a[r]);
            --r;
            for(;r-l>=lowbit(r);r-=lowbit(r))
                ans=std::max(ans,a[r]);
        }
        return ans;
    }
    T max(int x) {
        T ans=0;
        for(int i=x;i>0;i-=lowbit(i)) ans=std::max(ans,a[i]);
        return ans;
    }
};

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin>>n;
    vector<PII>aa(n+1); // first->value; seconde->position
    for(int i=1;i<=n;++i){
        cin>>aa[i].first; aa[i].second=i;
    }
    std::sort(aa.begin()+1,aa.end(),[](const PII&x,const PII&y){
        return x.first==y.first ? x.second>y.second : x.first<y.first;
    });

    max_FenwickTree<int>mFT(n);
    for(int i=1;i<=n;++i){

    }
    return 0;
} */
/* 
int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin>>n;
    vector<int>L;
    while(n--){
        int now; cin>>now;
        if(L.empty()||now>L.back()){
            L.emplace_back(now);
            continue;
        }
        if(now<L.back()){
            auto it=std::upper_bound(L.begin(),L.end(),now);
            *it=now;
        }
    }
    cout<<L.size()<<endl;
    return 0;
}
*/