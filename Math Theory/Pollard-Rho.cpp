/**
 * @brief   from 严格鸽
 *          https://zhuanlan.zhihu.com/p/591377294
 *          用于寻找一个数的所有质因数
 * @warning 求出来的质因数序列是无序的
 * @note    复杂度理论 $O(n^{\frac{1}{4}}\log n)$  但实际跑得快, 可以按 $O(n^{\frac{1}{4}})$ 算
 */
#include <bits/stdc++.h>

#include <random>
#include <chrono>

namespace prime_fac {
    const int S = 8; // 随机算法判定次数，8~10 就够了
    // 龟速乘
    int64_t mult_mod(int64_t a, int64_t b, int64_t c) {
        a %= c, b %= c;
        int64_t ret = 0;
        int64_t tmp = a;
        while (b) {
            if(b&1) {
                ret += tmp;
                if (ret > c) ret -= c;
            }
            tmp <<= 1;
            if (tmp > c) tmp -= c;
            b >>= 1;
        }
        return ret;
    }

    // 快速幂
    int64_t qow_mod(int64_t a, int64_t n, int64_t _mod) {
        int64_t ret = 1;
        int64_t temp = a % _mod;
        while (n) {
            if (n & 1) ret = mult_mod(ret, temp, _mod);
            temp = mult_mod(temp, temp, _mod);
            n >>= 1;
        }
        return ret;
    }

    // 是合数返回true，不一定是合数返回false
    bool check(int64_t a, int64_t n, int64_t x, int64_t t) {
        int64_t ret = qow_mod(a, x, n);
        int64_t last = ret;
        for (int i = 1; i <= t; i++) {
            ret = mult_mod(ret, ret, n);
            if (ret == 1 && last != 1 && last != n - 1) return true;
            last = ret;
        }
        if (ret != 1) return true;
        return false;
    }

    // 是素数返回true，不是返回false
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    bool Miller_Rabin(int64_t n) {
        if (n < 2) return false;
        if (n == 2) return true;
        if ((n & 1) == 0) return false;
        int64_t x = n - 1;
        int64_t t = 0;
        while ((x & 1) == 0) { x >>= 1; t++; }

        for (int i = 0; i < S; i++) {
            int64_t a = rng() % (n - 1) + 1;
            if (check(a, n, x, t))
                return false;
        }

        return true;
    }

    int64_t factor[100];// 存质因数
    int tol; // 质因数的个数，0~tol-1

    int64_t gcd(int64_t a, int64_t b) {
        int64_t t;
        while (b) {
            t = a;
            a = b;
            b = t % b;
        }
        if (a >= 0) return a;
        return -a;
    }

    int64_t pollard_rho(int64_t x, int64_t c) {
        int64_t i = 1, k = 2;
        int64_t x0 = rng() % (x - 1) + 1;
        int64_t y = x0;
        while (1) {
            i++;
            x0 = (mult_mod(x0, x0, x) + c) % x;
            int64_t d = gcd(y - x0, x);
            if (d != 1 && d != x) return d;
            if (y == x0) return x;
            if (i == k) { y = x0; k += k; }
        }
    }
    // 对n质因数分解，存入factor，k一般设置为107左右
    void findfac(int64_t n, int k) {
        if (n == 1) return;
        if (Miller_Rabin(n)) {
            factor[tol++] = n;
            return;
        }
        int64_t p = n;
        int c = k;
        while (p >= n) p = pollard_rho(p, c--);
        findfac(p, k);
        findfac(n / p, k);
    }

    std::vector<int64_t> fac(int64_t n) {
        tol = 0;
        std::vector<int64_t> ret;
        findfac(n, 107);
        for(int i=0;i<tol;i++) ret.push_back(factor[i]);
        return ret;
    }
} // namespace prime_fac


// how to use
int main()
{
    int64_t n; std::cin >> n;
    std::vector<int64_t> fac = std::move(prime_fac::fac(n));
}