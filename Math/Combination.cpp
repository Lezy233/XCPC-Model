#include <bits/stdc++.h>

typedef long long ll;

ll power(ll a,ll b,ll mod) { // a^b%mod
    ll res=1;
    for(a%=mod; b; a=a*a%mod, b>>=1) if(b&1) (res*=a)%=mod;
    return res;
}

// @brief   使用 Lucas 定理求解，适用于 MOD 较小的场景
ll nCr(ll n, ll m ,ll MOD) {
    auto C=[](ll _n,ll _m)->ll{
        if(_m>_n) return 0;
        ll ans=1;
        for(ll i=1,j=_n;j<=_m;++i,--j){
            (ans*=j)%=MOD;
            (ans*=power(i,MOD-2,MOD))%=MOD;
        }
        return ans;
    };
    
    if(n<m&&m<MOD) return C(n,m);
    return C(n%MOD,m%MOD) * nCr(n/MOD,m/MOD) % MOD;
}

/* ll MOD;
std::vector<ll>fac;

ll inv(ll x){ return x==1? 1:power(x,MOD-2,MOD); }
ll nPr(ll n,ll m){ return fac[n]*inv(fac[n-m])%MOD; }
ll nCr(ll n,ll m){ return fac[n]*inv(fac[n-m])%MOD*inv(fac[m])%MOD; } */



int main()
{
    
}