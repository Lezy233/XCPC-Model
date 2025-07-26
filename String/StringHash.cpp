#include <bits/stdc++.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

bool isPrime(int n) {
    if(n <= 1) return false;
    for(int i=2; i*i<=n; ++i) if(n%i == 0) return false;
    return true;
}
int findPrime(int n) {
    while(!isPrime(n)) ++n;
    return n;
}

template <size_t N>
class StringHash {
private:
    static std::array<int, N> mod;
    static std::array<int, N> base;
    std::vector<std::array<int, N>> p, h;
public:
    StringHash() = default;
    StringHash(const std::string &s) {
        int n = s.size();
        p.resize(n);
        h.resize(n);
        std::fill(p[0].begin(), p[0].end(), 1);
        std::fill(h[0].begin(), h[0].end(), 1);
        for(int i=0; i<n; ++i)
            for(int j=0; j<N; ++j) {
                p[i][j] = 1LL * (i==0? 1LL:p[i-1][j]) * base[j] % mod[j];
                h[i][j] = (1LL * (i==0? 0ll:h[i-1][j])*base[j]+s[i]) % mod[j];
            }
    }
    std::array<int, N> query(int l, int r) {
        assert(r >= l-1);
        if(l>r) return {0, 0};
        std::array<int, N> ans{};
        for(int i=0; i<N; i++) {
            ans[i] = h[r][i] - 1LL
                    * (l==0? 0LL : h[l-1][i])
                    * (r-l+1==0? 1LL : p[r-l][i])
                    % mod[i];
            if(ans[i] < 0) ans[i] += mod[i];
        }
        return ans;
    }
    void push_back(const char &ch) {
        int n = p.size(), m = h.size();
        if(n == m) {
            p.push_back({});
            for(int j=0; j<N; ++j)
                p[n][j] = 1LL * (n==0? 1LL:p[n-1][j]) * base[j] % mod[j];
            ++n;
        }
        h.emplace_back();
        for(int j=0; j<N; ++j)
            h[m][j] = (1LL * (m==0? 0LL:h[m-1][j]) * base[j] + ch) % mod[j];
    }
    void pop_back() {
        assert(!h.empty());
        h.pop_back();
    }
};

constexpr size_t HN = 2;
template <>
std::array<int, 2> StringHash<HN>::mod = {
    findPrime(rng() % 900'000'000 + 100'000'000),
    findPrime(rng() % 900'000'000 + 100'000'000)
};
template <>
std::array<int, 2> StringHash<HN>::base{13331, 131};
using Hashing = StringHash<HN>;

int main()
{
    std::string S = "SadOvO";
    Hashing hashS(S);
    std::ranges::reverse(S);
    Hashing hashS2(S);
    std::cout << (hashS.query(3, 5) == hashS2.query(0, 2) ? "YES\n" : "NO\n");
    std::cout << (hashS.query(0, 2) == hashS2.query(3, 5) ? "YES\n" : "NO\n");
}