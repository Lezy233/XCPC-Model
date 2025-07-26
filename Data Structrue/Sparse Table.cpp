#include<bits/stdc++.h>

std::vector<int> Log2;

template <class T>
class SparseTable { // 使用ST表前请自备Log2[]数组
private:
    int n;
    std::vector<std::vector<T>> info;
    std::function<T(const T&, const T&)> cmp; // 比较函数
    constexpr T check(const T &lhs, const T &rhs) {
        return cmp(lhs, rhs)? lhs : rhs;
    }
public:
    // vec 1-indexed
    SparseTable(const std::vector<T> &vec, std::function<T(const T&, const T&)> compare = std::greater<T>())
    : n(vec.size()-1), cmp(compare) {
        if(Log2.size() <= n) {
            int i = std::max(int(Log2.size()), 2);
            Log2.resize(n+1);
            Log2[1] = 0;
            for(; i<=n; ++i) Log2[i] = Log2[i>>1] + 1;
        }
        info.resize(n+1, std::vector<T>(Log2[n]+1));
        for(int i=1; i<=n; ++i) info[i][0] = vec[i];
        for(int j=1; j<=Log2[n]; ++j)
            for(int i=1; i-1+(1<<j)<=n; ++i)
                info[i][j] = check(info[i][j-1], info[i+(1<<j-1)][j-1]);
    }
    T find(int L, int R) {
        int len = Log2[R-L+1];
        return check(info[L][len], info[R+1-(1<<len)][len]);
    }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; std::cin >> n >> m;
    std::vector<int> aa(n+1);
    for(int i = 1; i <= n; ++i)
        std::cin >> aa[i];
    SparseTable<int> ST(aa); // 默认是取最大值
    // SparseTable<int> maxST(aa, std::greater<int>()); // 取最大值
    // SparseTable<int> minST(aa, std::less<int>()); // 取最小值
    while(m--) {
        int l,r; std::cin >> l >> r;
        std::cout << ST.find(l, r) << "\n";
    }
    return 0;
}