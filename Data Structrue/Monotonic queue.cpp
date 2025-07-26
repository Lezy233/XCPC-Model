// P1886 AC
#include<bits/stdc++.h>
using std::cin,std::cout,std::endl,std::min;
const int INF=0x3f3f3f3f;

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n,k; cin>>n>>k;
    std::vector<int>aa(n+1);
    std::deque<int>dq; //dq中记录的是标号
    for(int i=1;i<=n;++i) cin>>aa[i];

    for(int i=1;i<=n;++i){
        while(!dq.empty()&&aa[i]<=aa[*dq.rbegin()]) dq.pop_back();
        dq.emplace_back(i);
        if(i>=k){
            while(dq.front()<=i-k) dq.pop_front();
            cout<<aa[dq.front()]<<" ";
        }
    }
    cout<<endl;

    dq.clear(); 
    for(int i=1;i<=n;++i){
        while(!dq.empty()&&aa[i]>=aa[*dq.rbegin()]) dq.pop_back();
        dq.emplace_back(i);
        if(i>=k){
            while(dq.front()<=i-k) dq.pop_front();
            cout<<aa[dq.front()]<<" ";
        }
    }
    return 0;
}