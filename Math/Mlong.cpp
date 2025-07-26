#include <bits/stdc++.h>

typedef long long ll;

template <typename T>
constexpr T power(T a,ll b) {
    T res=1;
    for(;b;b>>=1, a*=a) if(b&1) res*=a;
    return res;
}

constexpr ll mul(ll a,ll b,ll MOD) {
    ll res=a*b-ll(1.L*a*b/MOD)*MOD;
    if(res%=MOD; res<MOD) res+=MOD;
    return res;
}

template <long long P>
class Mlong {
public:
    ll x;
    static ll MOD;
    constexpr Mlong(): x() {}
    constexpr Mlong(ll _x): x{norm(x%getMOD())} {}

    constexpr static void setMOD(ll _MOD){ MOD=_MOD; }
    constexpr static ll getMOD(){ return P>0? P:MOD; }
    constexpr ll norm(ll x) const { return x>=0&&x<getMOD()? x:(x<0?x+=getMOD():x-=getMOD()); }
    constexpr ll val() const { return x; }
    explicit constexpr operator ll() const { return x; }
    constexpr Mlong operator-() const { Mlong res; res.x=norm(getMOD()-x); return res; }
    constexpr Mlong inv() const { assert(x!=0); return power(*this.x,getMOD()-2); }
    constexpr Mlong &operator*=(Mlong rhs)&{ x=mul(x,rhs.x,getMOD()); return *this; }
    constexpr Mlong &operator+=(Mlong rhs)&{ x=norm(x+rhs.x); return *this; }
    constexpr Mlong &operator-=(Mlong rhs)&{ x=norm(x-rhs.x); return *this; }
    constexpr Mlong &operator/=(Mlong rhs)&{ return *this*=rhs.inv(); }
    friend constexpr Mlong operator*(Mlong lhs, Mlong rhs){ Mlong res=lhs; res*=rhs; return res; }
    friend constexpr Mlong operator+(Mlong lhs, Mlong rhs){ Mlong res=lhs; res+=rhs; return res; }
    friend constexpr Mlong operator-(Mlong lhs, Mlong rhs){ Mlong res=lhs; res-=rhs; return res; }
    friend constexpr Mlong operator/(Mlong lhs, Mlong rhs){ Mlong res=lhs; res/=rhs; return res; }
    friend constexpr std::istream &operator>>(std::istream &is, Mlong &a){ ll v; is>>v; a=Mlong(v); return is; }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mlong &a){ return os<<a.val(); }
    friend constexpr bool operator==(Mlong lhs, Mlong rhs){ return lhs.val() == rhs.val(); }
    friend constexpr bool operator!=(Mlong lhs, Mlong rhs){ return lhs.val() != rhs.val(); }
};

template <>
ll Mlong<0LL>::MOD=ll(1e18)+9;

template <int P>
class Mint {    
public:
    int x;
    static int MOD;
    constexpr Mint(): x() {}
    constexpr Mint(long long _x): x{norm(_x%getMOD())} {}

    constexpr static void setMOD(int _MOD){ MOD=_MOD; }
    constexpr static int getMOD(){ return P>0?P:MOD; }
    constexpr int norm(int x) const { return x>=0&&x<getMOD()? x:(x<0?x+=getMOD():x-=getMOD()); }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr Mint operator-() const { Mint res; res.x=norm(getMOD()-x); return res;}
    constexpr Mint inv() const{ assert(x!=0); return power(*this,getMOD()-2); }
    constexpr Mint &operator*=(Mint rhs)&{ x=1LL*x*rhs.x%getMOD(); return *this; }
    constexpr Mint &operator+=(Mint rhs)&{ x=norm(x+rhs.x); return *this; }
    constexpr Mint &operator-=(Mint rhs)&{ x=norm(x-rhs.x); return *this; }
    constexpr Mint &operator/=(Mint rhs)&{ return *this*=rhs.inv(); }
    friend constexpr Mint operator*(Mint lhs, Mint rhs){ Mint res=lhs; res*=rhs; return res; }
    friend constexpr Mint operator+(Mint lhs, Mint rhs){ Mint res=lhs; res+=rhs; return res; }
    friend constexpr Mint operator-(Mint lhs, Mint rhs){ Mint res=lhs; res-=rhs; return res; }
    friend constexpr Mint operator/(Mint lhs, Mint rhs){ Mint res=lhs; res/=rhs; return res; }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a){ long long v; is>>v; a=Mint(v); return is; }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a){ return os<<a.val(); }
    friend constexpr bool operator==(Mint lhs, Mint rhs){ return lhs.val()==rhs.val(); }
    friend constexpr bool operator!=(Mint lhs, Mint rhs){ return lhs.val()!=rhs.val(); }
};

template <>
int Mint<0>::MOD=998244353;

template<int V, int P>
constexpr Mint<P> Cinv = Mint<P>(V).inv();

constexpr int P=1e9+7; // 可以修改这里的P 如果需要将变量设为P,需要将P变为0
using Z=Mint<P>;