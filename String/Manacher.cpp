// Manacher 最长连续回文子串个数

// P3805
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef long long ll;

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    std::string tt,S="&"; cin>>tt;
    for(auto ch:tt) S+="#", S+=ch;
    S+="#$";
    int n=S.size(), res=0;
    vector<int>P(n,1);
    for(int i=1,R=1,C=1;i<n-1;++i){
        if(i<R) P[i]=std::min(P[C*2-i],P[C]+C-i);
        while(S[i+P[i]]==S[i-P[i]]) ++P[i];
        if(i+P[i]>R){
            R=i+P[i]; C=i;
        }
        res=std::max(res,P[i]-1);
    }
    cout<<res<<endl;
    return 0;
}