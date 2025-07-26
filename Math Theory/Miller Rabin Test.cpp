#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;

/*
维基百科 :
n < 4e9, Prime = [2, 7, 61]
n < 3e14, Prime = [2, 3, 5, 7, 11, 13, 17]
n < 3e18, Prime = [2, 3, 5, 7, 11, 13, 17, 19, 23]
n < 3e23, Prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
*/
template <class T>
struct MillerRabin {
    const std::vector<int> Prime;
    MillerRabin() : Prime({2, 3, 5, 7, 11, 13, 17, 19, 23}) {}

    static constexpr int mulp(const int &a, const int &b, const int &P) {
        return 1LL * a * b % P;
    }
    static constexpr int64_t mulp(const int64_t &a, const int64_t &b, const int64_t &P) {
        int64_t res = a * b - i64(1.L * a * b / P) * P;
        res %= P;
        res += (res < 0 ? P : 0);
        return res;
    }

    static constexpr T power(T a, T b, const T &MOD) { // a^b mod MOD
        T ans = 1;
        for (; b; b >>= 1) {
            if (b & 1)
                ans = mulp(ans, a, MOD);
            a = mulp(a, a, MOD);
        }
        return ans;
    }

    constexpr bool operator()(const T &v) { // 判断v是不是质数
        if (v < 2 || v != 2 && v % 2 == 0)
            return false;
        T s = v - 1;
        while (!(s & 1))
            s >>= 1;
        for (int x : Prime) {
            if (v == x)
                return true;
            T t = s, m = power(x, s, v);
            while (t != v - 1 && m != 1 && m != v - 1)
                m = mulp(m, m, v), t <<= 1;
            if (m != v - 1 && !(t & 1))
                return false;
        }
        return true;
    }
};
MillerRabin<int64_t> isp;

