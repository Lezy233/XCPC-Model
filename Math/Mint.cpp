#include <bits/stdc++.h>

template <typename T>
constexpr T power(T a,long long b){ T res=1; for(;b;b>>=1, a*=a) if(b&1) res*=a; return res; }
template <int P>
class Mint {    
public:
    int x;
    static int MOD;
    constexpr Mint(): x() {}
    constexpr Mint(long long _x): x{norm(_x%getMOD())} {}

    constexpr static void setMOD(int _MOD) { MOD = _MOD; }
    constexpr static int getMOD() { return P>0 ? P : MOD; }
    constexpr int norm(int x) const {
        return x >= 0 && x < getMOD()
               ? x
               : (x<0 ? x+=getMOD() : x-=getMOD());
    }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(getMOD()-x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, getMOD()-2);
    }
    constexpr Mint &operator*=(Mint rhs)&{ x = 1LL*x*rhs.x%getMOD(); return *this; }
    constexpr Mint &operator+=(Mint rhs)&{ x = norm(x+rhs.x); return *this; }
    constexpr Mint &operator-=(Mint rhs)&{ x = norm(x-rhs.x); return *this; }
    constexpr Mint &operator/=(Mint rhs)&{ return *this *= rhs.inv(); }
    friend constexpr Mint operator*(Mint lhs, Mint rhs){ Mint res=lhs; res*=rhs; return res; }
    friend constexpr Mint operator+(Mint lhs, Mint rhs){ Mint res=lhs; res+=rhs; return res; }
    friend constexpr Mint operator-(Mint lhs, Mint rhs){ Mint res=lhs; res-=rhs; return res; }
    friend constexpr Mint operator/(Mint lhs, Mint rhs){ Mint res=lhs; res/=rhs; return res; }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        long long v; is>>v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a){ return os<<a.val(); }
    friend constexpr bool operator==(Mint lhs, Mint rhs){ return lhs.val()==rhs.val(); }
    friend constexpr bool operator!=(Mint lhs, Mint rhs){ return lhs.val()!=rhs.val(); }
};

template <>
int Mint<0>::MOD = 998244353;

template<int V, int P>
constexpr Mint<P> Cinv = Mint<P>(V).inv();

constexpr int P = 1e9+7; // 可以修改这里的P 如果需要将变量设为P,需要将P变为0
using Z = Mint<P>;