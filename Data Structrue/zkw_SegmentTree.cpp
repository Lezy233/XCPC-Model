/**
 * @brief   zkw-Segment, Segment Tree但不用递归实现
*/

#include <bits/stdc++.h>

/**
 * @note    支持单点修改 区间查询
*/
template <typename T>
class zkw_SegmentTree {
private:
    int N;
    std::vector<T>tree;
public:
    zkw_SegmentTree(int n): N(1<<(int)std::log2(n+1)+1), tree(1<<int(std::log2(n+1))+2) {}
    // vector a is 0-index, but segmenttree is 1-index
    zkw_SegmentTree(std::vector<T>&a): zkw_SegmentTree(a.size()) {
        for(int i=1;i<=a.size();++i) tree[i+N]=a[i-1];
        for(int i=N-1;i;--i) tree[i]=tree[i<<1]+tree[i<<1|1];
    }
    // 单点修改
    void pointAdd(int x, T d) {
        for(x+=N; x; x>>=1) tree[x]+=d;
    }
    // 区间查询
    T rangeQuery(int L, int R) {
        T ans=0;
        for(L+=N-1, R+=N-1; L^R^1; L>>=1, R>>=1){
            if(~L&1) ans+=tree[L^1];
            if(R&1) ans+=tree[R^1];
        }
        return ans;
    }
};

/**
 * @note    支持单点修改 区间修改 区间查询
*/
template <typename T>
class zkw_SegmentTree {
private:
    int N;
    std::vector<T>tree, tag;
public:
    zkw_SegmentTree(int n): N(1<<(int)std::log2(n+1)+1), tree(N<<1), tag(N<<1) {};
    // vector a is 0-index, but segmenttree is 1-index
    zkw_SegmentTree(std::vector<T>&a): zkw_SegmentTree(a.size()) {
        for(int i=1;i<=a.size();++i) tree[i+N]=a[i-1];
        for(int i=N-1;i;--i) tree[i]=tree[i<<1]+tree[i<<1|1];
    }
    // 单点修改
    void pointAdd(int x,T d) {
        for(x+=N; x; x>>=1) tree[x]+=d;
    }
    
    void rangeAdd(int L,int R,T d) {
        int len=1, cntL=0, cntR=0; // cntL, cntR是左右两边分别实际修改的区间长度
        for(L+=N-1, R+=N+1; L^R^1; L>>=1, R>>=1, len<<=1){
            tree[L]+=cntL*d, tree[R]+=cntR*d;
            if(~L&1) tree[L^1]+=len*d, tag[L^1]+=d, cntL+=len;
            if(R&1) tree[R^1]+=len*d, tag[R^1]+=d, cntR+=len;
        }
        for(; L; L>>=1, R>>=1) tree[L]+=cntL*d, tree[R]+=cntR*d;
    }

    T rangeQuery(int L,int R) {
        T ans=0;
        int len=1, cntL=0, cntR=0;
        for(L+=N-1, R+=N+1; L^R^1; L>>=1, R>>=1, len<<=1) {
            ans+=cntL*tag[L]+cntR*tag[R];
            if(~L&1) ans+=tree[L^1], cntL+=len;
            if(R&1) ans+=tree[R^1], cntR+=len;
        }
        for(; L; L>>=1, R>>=1) ans+=cntL*tag[L]+cntR*tag[R];
        return ans;
    }
};

int main()
{
    int n,m; std::cin>>n>>m;
    std::vector<long long>aa(n);
    for(auto &i:aa) std::cin>>i;
    zkw_SegmentTree<long long> zST(aa);
    while(m--){
        int opt; std::cin>>opt;
        if(opt==1){
            long long x,y,k; std::cin>>x>>y>>k;
            zST.rangeAdd(x,y,k);
        }
        else{
            int x,y; std::cin>>x>>y;
            std::cout<<zST.rangeQuery(x,y)<<std::endl;
        }
    }
    return 0;
}