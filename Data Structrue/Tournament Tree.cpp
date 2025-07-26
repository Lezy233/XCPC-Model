/**
 * @brief   Tournament Tree  树套树
*/

#include <bits/stdc++.h>

/** @brief  P3380
 *          树套树 外层线段树 内层平衡树
 *          但是这个代码因为封装得太强，被卡常了 QAQ
*/

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class FHQ_Treap{
private:
    #define ls son[0]
    #define rs son[1]
    struct Node{
        Node *son[2]; // son[0]:ls, son[1]:rs
        T val;
        int rank,cnt,siz;
        Node(T val_): val(val_), cnt(1), siz(1) {
            son[0]=son[1]=nullptr;
            rank=rng();
        }
        void update_siz(){
            siz=cnt;
            if(ls) siz+=ls->siz;
            if(rs) siz+=rs->siz;
        }
    };
    Node *root;

    std::pair<Node*,Node*> split(Node *cur, T key) { // <=, >
        if(cur==nullptr) return {nullptr,nullptr};
        if(cur->val <= key){
            auto [rsL,rsR]=split(cur->rs,key);
            cur->rs=rsL;
            cur->update_siz();
            return {cur,rsR};
        }
        else{
            auto [lsL,lsR]=split(cur->ls,key);
            cur->ls=lsR;
            cur->update_siz();
            return {lsL,cur};
        }
    }

    std::tuple<Node*,Node*,Node*> splitRank(Node *cur, int rank_) {
        if(cur==nullptr) return {nullptr,nullptr,nullptr};
        int ls_siz=cur->ls? cur->ls->siz:0;
        Node *l,*mid,*r;
        if(rank_<=ls_siz){
            std::tie(l,mid,r)=splitRank(cur->ls,rank_);
            cur->ls=r;
            cur->update_siz();
            return {l,mid,cur};
        }
        else if(rank_<=ls_siz+cur->cnt){
            l=cur->ls, r=cur->rs;
            cur->ls=cur->rs=nullptr;
            return {l,cur,r};
        }
        else{
            std::tie(l,mid,r)=splitRank(cur->rs,rank_-ls_siz-cur->cnt);
            cur->rs=l;
            cur->update_siz();
            return {cur,mid,r};
        }
    }

    Node *merge(Node *u,Node *v) { // 合并u,v并返回父节点
        if(u==nullptr) return v;
        if(v==nullptr) return u;
        if(u->rank < v->rank){ // 小根堆
            u->rs=merge(u->rs,v); u->update_siz(); return u;
        }
        else{
            v->ls=merge(u,v->ls); v->update_siz(); return v;
        }
    }

    T queryVal(Node *cur, int rank_) { // 根据排名查询值
        auto [l,mid,r]=splitRank(cur,rank_);
        T ans=mid->val;
        root=merge(merge(l,mid),r);
        return ans;
    }

    // @warning 排名不+1 为了方便树套树
    int queryRank(Node *cur, T v_) { // 根据值查询排名
        auto [rtL,rtR]=split(cur,v_-1);
        int ans=(rtL? rtL->siz:0);
        root=merge(rtL,rtR);
        return ans;
    }

public:
    FHQ_Treap(): root(nullptr) {}
    FHQ_Treap(T NotFind): root(nullptr) {}
    void insert(T val) {
        auto [rtL,rtR]=split(root,val);
        auto [lsL,lsR]=split(rtL,val-1);
        Node *tt;
        if(lsR==nullptr) tt=new Node(val);
        else{ ++lsR->cnt; lsR->update_siz(); }
        Node *new_rtL=merge(lsL,lsR? lsR:tt);
        root=merge(new_rtL,rtR);
    }

    void del(T val) {
        auto [rtL,rtR]=split(root,val);
        auto [lsL,lsR]=split(rtL,val-1);
        if(lsR->cnt > 1){
            --lsR->cnt;
            lsR->update_siz();
            lsL=merge(lsL,lsR);
        }
        else{
            if(rtL==lsR) rtL=nullptr;
            delete lsR;
            lsR=nullptr;
        }
        root=merge(lsL,rtR);
    }


    int queryRank_byVal(T val){ return queryRank(root,val); }
    T queryVal_byRank(int rank){ return queryVal(root,rank); }

    T queryPre(T val) { // 查询x的前驱(小于x的最大的值)
        auto [rtL,rtR]=split(root,val-1);
        T ans=rtL? queryVal(rtL,rtL->siz):-2147483647;
        root=merge(rtL,rtR);
        return ans;
    }

    T queryNxt(T val){ // 查询x的后继(大于x的最小的值)
        auto [rtL,rtR]=split(root,val);
        T ans=rtR? queryVal(rtR,1):2147483647;
        root=merge(rtL,rtR);
        return ans;
    }
    
    #undef ls
    #undef rs
};

template <typename T>
class SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    #define mid (rtL+rtR>>1)
    std::vector<FHQ_Treap<T>> info;

    void init(std::vector<T>&_init) {
        auto build=[&](auto self,int rt,int rtL,int rtR){
            for(int i=rtL;i<=rtR;++i) info[rt].insert(_init[i]);
            if(rtL==rtR) return;
            self(self,ls,rtL,mid);
            self(self,rs,mid+1,rtR);
        };
        build(build,1,1,n);
    }

    void _update(int rt,int rtL,int rtR,int pos,int u,int v) { // pos上的u改成v
        info[rt].del(u);
        info[rt].insert(v);
        if(rtL==rtR) return;
        if(pos<=mid) _update(ls,rtL,mid,pos,u,v);
        else _update(rs,mid+1,rtR,pos,u,v);
    }

    int _queryRank_byVal(int rt,int rtL,int rtR,int L,int R,T val){
        if(L<=rtL&&rtR<=R) return info[rt].queryRank_byVal(val);
        int ans=0;
        if(L<=mid) ans+=_queryRank_byVal(ls,rtL,mid,L,R,val);
        if(R>mid) ans+=_queryRank_byVal(rs,mid+1,rtR,L,R,val);
        return ans;
    }

    int _queryPre(int rt,int rtL,int rtR,int L,int R,T val) {
        if(L<=rtL&&rtR<=R) return info[rt].queryPre(val);
        int ans=-2147483647;
        if(L<=mid) ans=std::max(ans,_queryPre(ls,rtL,mid,L,R,val));
        if(R>mid) ans=std::max(ans,_queryPre(rs,mid+1,rtR,L,R,val));
        return ans;
    }

    int _queryNxt(int rt,int rtL,int rtR,int L,int R,T val) {
        if(L<=rtL&&rtR<=R) return info[rt].queryNxt(val);
        int ans=2147483647;
        if(L<=mid) ans=std::min(ans,_queryNxt(ls,rtL,mid,L,R,val));
        if(R>mid) ans=std::min(ans,_queryNxt(rs,mid+1,rtR,L,R,val));
        return ans;
    }

    #undef ls
    #undef rs
    #undef mid

public:
    int n;
    SegmentTree() {};
    SegmentTree(int n, std::vector<T>&_init): n(n), info(4<<std::__lg(n), FHQ_Treap<T>()){
        init(_init);
    }

    void update(int pos,int u,int v) { _update(1,1,n,pos,u,v); }
    int queryRank_byVal(int L,int R,T val) { return _queryRank_byVal(1,1,n,L,R,val)+1; }
    int queryVal_byRank(int L,int R,int rank) {
        int l=0, r=1e8;
        while(l<=r){
            int mid=l+r>>1;
            if(queryRank_byVal(L,R,mid)<=rank) l=mid+1;
            else r=mid-1;
        }
        return r;
    }
    int queryPre(int L,int R,T val) { return _queryPre(1,1,n,L,R,val); }
    int queryNxt(int L,int R,T val) { return _queryNxt(1,1,n,L,R,val); }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; std::cin>>n>>m;
    std::vector<int>aa(n+1);
    for(int i=1;i<=n;++i) std::cin>>aa[i];
    SegmentTree<int>ST(n,aa);
    while(m--){
        int opt,l,r,k,pos; std::cin>>opt;
        switch(opt){
        case 1:
            std::cin>>l>>r>>k;
            std::cout<<ST.queryRank_byVal(l,r,k)<<'\n';
            break;
        case 2:
            std::cin>>l>>r>>k;
            std::cout<<ST.queryVal_byRank(l,r,k)<<'\n';
            break;
        case 3:
            std::cin>>pos>>k;
            ST.update(pos,aa[pos],k);
            aa[pos]=k;
            break;
        case 4:
            std::cin>>l>>r>>k;
            std::cout<<ST.queryPre(l,r,k)<<'\n';
            break;
        case 5:
            std::cin>>l>>r>>k;
            std::cout<<ST.queryNxt(l,r,k)<<'\n';
            break;
        }
    }
    return 0;
}