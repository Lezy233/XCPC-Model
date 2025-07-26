#include<bits/stdc++.h>

template <class T>
class FenwickTree {
private:
    int n;
    std::vector<T> a;
    constexpr auto lowbit(auto x) { return x&-x; }
public:
    FenwickTree(size_t _n): n(_n), a(_n+1) {}
    void add(int pos, T v) { for(int i=pos; i<=n; i+=lowbit(i)) a[i] = a[i] + v; }
    void init(size_t n, T val = T{}) {
        this->n = n;
        a.assign(n+1, val);
    }
    T sum(int x) {
        T ans{};
        for (int i=x; i>0; i-=lowbit(i)) ans = ans + a[i];
        return ans;
    }
    T rangeSum(int l, int r) { return l<=r ? sum(r)-sum(l-1) : 0; }
};

struct Max {
    int val = -1;
    Max operator+(const Max &rhs) const {
        return Max{std::max(val, rhs.val)};
    }
};

template <typename T>
class Two_dimen_FenwickTree { // 二维树状数组
private:
    using PII = std::pair<int,int>;

    int n,m;
    std::vector<std::vector<std::vector<T>>> a;
    int lowbit(int x) { return x&-x; }
public:
    Two_dimen_FenwickTree(int _n,int _m): n(_n), m(_m) {
        a.resize(4);
        for (int i=0 ;i<4 ;++i) a[i].resize(_n+3,std::vector<T>(_m+3));
    }

    void init(int _n,int _m) {
        this->n = _n; a.resize(4);
        for(int i=0;i<4;++i)
            a[i].resize(_n+3,std::vector<T>(_m+3));
    }

    void add_point(int x,int y,T d){
        for(int i=x;i<=n;i+=lowbit(i)){
            for(int j=y;j<=m;j+=lowbit(j)){
                a[0][i][j]+=d; a[1][i][j]+=x*d; a[2][i][j]+=y*d; a[3][i][j]+=x*y*d;
            }
        }
    }

    void add(int x1,int y1,int x2,int y2,T d){
        add_point(x1,y1,d); add_point(x2+1,y2+1,d); add_point(x1,y2+1,-d); add_point(x2+1,y1,-d);
    }
    void add(PII p1,PII p2,T d){
        add(p1.first,p1.second,p2.first,p2.second,d);
    }

    T sum(int x,int y){
        T ans=0;
        for(int i=x;i>0;i-=lowbit(i))
            for(int j=y;j>0;j-=lowbit(j))
                ans+=(x+1)*(y+1)*a[0][i][j]-(y+1)*a[1][i][j]-(x+1)*a[2][i][j]+a[3][i][j];
        return ans;
    }

    T rangeSum(int x1,int y1,int x2,int y2){
        return sum(x2,y2)+sum(x1-1,y1-1)-sum(x1-1,y2)-sum(x2,y1-1);
    }
    T rangeSum(PII p1,PII p2){
        return rangeSum(p1.first,p1.second,p2.first,p2.second);
    }
};



template <typename T>
class max_Two_dimen_FenwickTree {
    // WARNING: 仅支持从(1,1)到(x,y)的最大值查询
private:
    int n,m;
    std::vector<std::vector<T>>a;

    int lowbit(int x){ return x&-x; }
public:
    max_Two_dimen_FenwickTree(int _n,int _m): n(_n), m(_m) {
        a.resize(_n+3,std::vector<T>(_m+3));
    }

    void update_point(int x,int y,T d) {
        // change (x,y) to d
        for(int i=x;i<=n;i+=lowbit(i))
            for(int j=y;j<=m;j+=lowbit(j))
                a[i][j]=std::max(a[i][j],d);
    }

    T max(int x,int y) {
        T ans=0;
        for(int i=x,i>0;i-=lowbit(i))
            for(int j=y;j>0;j-=lowbit(j))
                ans=std::max(ans,a[i][j]);
        return ans;
    }
};