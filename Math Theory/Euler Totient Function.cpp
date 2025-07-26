/**
 * @brief Euler's Totient Function 欧拉函数
 * @note \phi (x) 返回 <= x 且与 x 互质的数字个数
 */
#include <bits/stdc++.h>

int64_t Euler_Phi(int64_t n) { // 返回 n 的欧拉函数的值
    int64_t ans = n;
    for(int64_t i = 2; i * i <= n; ++i) {
        if(n % i) continue;
        ans -= ans / i;
        while(n % i == 0) n /= i;
    }
    if(n > 1) ans -= ans / n;
    return ans;
}

constexpr int MOD = 1e9+7;

/// @brief bas ^ exp % mod 
int64_t EulerDropPow(int64_t bas, int64_t exp, int mod, int phiMOD = -1) {
    if(phiMOD == -1) phiMOD = Euler_Phi(mod);
    int64_t ans = 1;
    exp = exp % phiMOD + phiMOD;
    for(bas %= mod; exp; bas = bas * bas % mod, exp >>= 1)
        if(exp & 1) ans = ans * bas % mod;
    return ans;
}

int32_t main()
{
    
}