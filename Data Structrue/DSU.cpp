/**
 * @brief 并查集全家桶
 */
#include <bits/stdc++.h>

/* 
/// @brief 带权并查集
template <class T>
class DSU {
private:
    std::vector<int> S;
    std::vector<T> dis; // dis[u]: distance of u->S[u]
public:
    DSU(size_t n): S(n), dis(n, 0) {
        std::iota(S.begin(), S.end(), 0);
    }
    
    int find(int x) {
        if(S[x] == x) return S[x];
        int t = S[x];
        S[x] = find(S[x]);
        dis[x] += dis[t];
        return S[x];
    }
    bool same(int u, int v) { return find(u) == find(v); }
    /// @brief add edge from u to v
    bool merge(int u, int v, T disUV) { // u->v
        int su = find(u), sv = find(v);
        if(su == sv) return false;
        S[su] = sv;
        dis[su] = disUV+dis[v]-dis[u];
        return true;
    }
    /// @brief get distance from u to v
    T getDis(int u, int v) {
        assert(same(u, v));
        return dis[u]-dis[v];
    }
};
 */

/// @brief 可撤销并查集
class DSU {
private:
    std::vector<int> siz, set;
    std::vector<std::pair<int&, int>> hsiz, hset; 
public:
    DSU(size_t n): siz(n, 1), set(n) {
        std::iota(set.begin(), set.end(), 0);
    } 
    int find(int x) { return x == set[x] ? x : find(set[x]); }
    bool same(int u, int v) { return find(u) == find(v); }
    int version() { return hsiz.size(); }

    bool merge(int u, int v) { // u->v
        u = find(u), v = find(v);
        if (u == v) return false;
        if (siz[u] > siz[v]) std::swap(u, v);
        hsiz.emplace_back(siz[v], siz[v]);
        siz[v] += siz[u];
        hset.emplace_back(set[u], set[u]);
        set[u] = v;
        return true;
    }
    /// @brief ver非负:滚回到第 ver 个版本; ver负数:滚回几个版本
    /// @param ver 版本号
    void roll(int ver = -1) {
        if (ver < 0) ver += hsiz.size();
        while (hsiz.size() > ver) {
            hset.back().first = hset.back().second;
            hset.pop_back();
            hsiz.back().first = hsiz.back().second;
            hsiz.pop_back();
        }
    }
};