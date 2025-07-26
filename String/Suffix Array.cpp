#include <bits/stdc++.h>

/**
 * @param 
 */

struct SA {
    size_t n;
    std::vector<int> sa; // sa[i]: 排名为 i 的后缀的编号
    std::vector<int> rk; // rk[i]: S[i:] 后缀排名
    std::vector<int> lc; // LCP 数组

    SA(const std::string &S): n(S.size()), sa(n), rk(n), lc(n-1) {
        std::iota(sa.begin(), sa.end(), 0);
        std::ranges::sort(sa,
            [&S](int a, int b) {
                return S[a] < S[b];
            }
        );
        rk[sa[0]] = 0;
        for(int i=1; i<n; ++i) {
            rk[sa[i]] = rk[sa[i-1]] + (S[sa[i]] != S[sa[i-1]]);
        }
        int k = 1;
        std::vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while(rk[sa[n-1]] < n-1) {
            tmp.resize(k);
            for(int i=0; i<k; ++i) tmp[i] = n - k + i;
            for(auto i:sa) if(i >= k) tmp.emplace_back(i - k);
            std::ranges::fill(cnt, 0);
            for(int i=0; i<n; ++i) ++cnt[rk[i]];
            for(int i=1; i<n; ++i) cnt[i] += cnt[i-1];
            for(int i=n-1; ~i; --i) sa[--cnt[rk[tmp[i]]]] = tmp[i];
            std::swap(rk, tmp);
            rk[sa[0]] = 0;
            for(int i=1; i<n; ++i)
                rk[sa[i]] = rk[sa[i-1]] +
                            (tmp[sa[i-1]] < tmp[sa[i]] || 
                            sa[i-1] + k == n || 
                            tmp[sa[i-1]+k] < tmp[sa[i]+k]);
            k *= 2;
        }
        for(int i=0, j=0; i<n; ++i) {
            if(rk[i] == 0) {
                j = 0;
            } else {
                for(j -= j>0; i+j < n && sa[rk[i]-1]+j < n && S[i+j] == S[sa[rk[i]-1]+j]; )
                    j++;
                lc[rk[i] - 1] = j;
            }
        }
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string S; std::cin >> S;
    
    
}