/// @brief 可持久化 01 Trie
// P4735 AC
#include <bits/stdc++.h>

struct Info {
    std::array<int, 2> son;
    int cnt;
    Info(): son{}, cnt(0) {}
};

std::vector<Info> info(1);

int insert(int pre, unsigned val) {
    int cur = info.size(), rt = cur;
    info.emplace_back(info[pre]);
    for(int i=31; ~i; --i) {
        int c = val>>i&1;
        info[cur].son[c] = info.size();
        info.emplace_back(info[info[pre].son[c]]);
        pre = info[pre].son[c];
        cur = info[cur].son[c];
        ++info[cur].cnt;
    }
    return rt;
}

unsigned getMax(int l, int r, unsigned val) {
    unsigned ans = 0;
    for(int i=31; ~i; --i) {
        int c = val>>i&1;
        if(info[info[l].son[c^1]].cnt < info[info[r].son[c^1]].cnt) {
            ans |= 1U<<i;
            l = info[l].son[c^1], r = info[r].son[c^1];
        } else {
            l = info[l].son[c], r = info[r].son[c];
        }
    }
    return ans;
}

void solve()
{
    int n,m; std::cin>>n>>m;
    std::vector<unsigned> aa(n+1);
    std::vector<int> root(n+2);
    for(int i=1; i<=n; ++i) {
        std::cin>>aa[i];
        aa[i] ^= aa[i-1];
    }
    root[1] = insert(root[0], 0);
    for(int i=2; i<=n+1; ++i)
        root[i] = insert(root[i-1], aa[i-1]);
    while(m--) {
        char opt; std::cin>>opt;
        if(opt == 'A') {
            unsigned x; std::cin>>x;
            aa.emplace_back(x^aa.back());
            root.emplace_back(insert(root.back(), aa.back()));
        } else {
            int l,r; unsigned x; std::cin>>l>>r>>x;
            auto res = getMax(root[l-1], root[r], x^aa.back());
            std::cout<<res<<"\n";
        }
    }
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