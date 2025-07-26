// P1484 AC
#include <bits/stdc++.h>
using std::cin, std::cout, std::vector, std::array;
using ll = long long;
using PII = std::pair<int, int>;
using PLI = std::pair<ll, int>;

void solve()
{
    int n,k; cin>>n>>k;
    vector<ll> aa(n+1);
    for(int i=1; i<=n; ++i) cin>>aa[i];

    vector<PII> it(n+2);
    for(int i=1; i<=n; ++i) it[i] = {i-1, i+1};
    it[0] = {0, 1}, it[n+1] = {n, n+1};
    
    vector<short> deled(n+1);
    
    std::priority_queue<PLI> pq;
    for(int i=1; i<=n; ++i) pq.emplace(aa[i], i);
    
    auto del = [&](int id) {
        auto [L, R] = it[id];
        deled[id] = 1;
        it[L].second = R, it[R].first = L;
    };

    ll res = 0;
    while(k-- && !pq.empty()) {
        auto [uVal, u] = pq.top(); pq.pop();
        if(uVal <= 0) break;
        if(deled[u]) { ++k; continue; }
        res += uVal;

        auto [L, R] = it[u];
        if(L != 0) del(L);
        if(R != n+1) del(R);
        if(L != 0 && R != n+1) {
            aa[u] = aa[L]+aa[R]-uVal;
            pq.emplace(aa[u], u);
        }
    }
    cout<<res<<"\n";
}

int32_t main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    std::ifstream in("C++/in.txt");
    std::cin.rdbuf(in.rdbuf());
#endif
    int T = 1;
    // std::cin>>T;
    while(T--) solve();
    return 0;
}