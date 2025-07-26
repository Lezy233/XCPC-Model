//P1226
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll power(ll a, ll b, ll mod) {
    ll res=1;
    for(a%=mod; b; a=a*a%mod, b>>=1) if(b&1) res=res*a%mod;
    return res;
}

int main()
{
    ll a,b,p; cin>>a>>b>>p;
    cout<<a<<"^"<<b<<" mod "<<p<<"="<<binpow(a,b,p)<<endl;
    return 0;
}