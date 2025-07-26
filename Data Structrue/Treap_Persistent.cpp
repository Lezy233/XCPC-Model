// P3835
#include <bits/stdc++.h>

/**
 * @brief   支持可持久化操作的平衡树
*/
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class FHQ_Treap {
private:
    #define ls son[0]
    #define rs son[1]
    struct Node {
        Node *son[2]; // son[0]:ls, son[1]:rs
        T val;
        int rank,cnt,siz;
        Node() = default;
        Node(T val_): val(val_), cnt(1), siz(1) {
            son[0] = son[1] = nullptr;
            rank = rng();
        }
        void update_siz() {
            siz = cnt;
            if (ls) siz += ls->siz;
            if (rs) siz += rs->siz;
        }
    };
    std::vector<Node*> root;

    std::pair<Node*,Node*> split(Node *cur, T key) { // <=, >
        if (cur == nullptr) return {nullptr, nullptr};
        Node *newCur = new Node(*cur);
        if (newCur->val <= key) {
            auto [rsL,rsR] = split(newCur->rs,key);
            newCur->rs = rsL;
            newCur->update_siz();
            return {newCur, rsR};
        } else {
            auto [lsL, lsR] = split(newCur->ls,key);
            newCur->ls = lsR;
            newCur->update_siz();
            return {lsL, newCur};
        }
    }

    std::tuple<Node*,Node*,Node*> splitRank(Node *cur, int rank_) {
        if(cur == nullptr) return {nullptr, nullptr, nullptr};
        Node *newCur = new Node(*cur);
        int ls_siz = newCur->ls? newCur->ls->siz : 0;
        Node *l, *mid, *r;
        if (rank_ <= ls_siz) {
            std::tie(l, mid, r) = splitRank(newCur->ls, rank_);
            newCur->ls = r;
            newCur->update_siz();
            return {l, mid, newCur};
        } else if (rank_ <= ls_siz+newCur->cnt) {
            l = newCur->ls, r = newCur->rs;
            newCur->ls = newCur->rs = nullptr;
            return {l, newCur, r};
        } else {
            std::tie(l, mid, r) = splitRank(newCur->rs, rank_-ls_siz-newCur->cnt);
            newCur->rs = l;
            newCur->update_siz();
            return {newCur, mid, r};
        }
    }

    Node *merge(Node *u,Node *v) { // 合并u,v并返回父节点
        if (u == nullptr) return v;
        if (v == nullptr) return u;
        if (u->rank < v->rank) { // 小根堆
            u->rs = merge(u->rs, v); u->update_siz(); return u;
        } else {
            v->ls = merge(u, v->ls); v->update_siz(); return v;
        }
    }

    T queryVal(Node *cur, int rank_, bool isCreat) { // 根据排名查询值 isCreat是否建立新节点
        auto [l, mid, r] = splitRank(cur, rank_);
        T ans = mid->val;
        if (isCreat) root.emplace_back(merge(merge(l, mid), r));
        return ans;
    }

    int queryRank(Node *cur, T v_) { // 根据值查询排名
        auto [rtL, rtR] = split(cur, v_-1);
        int ans = (rtL? rtL->siz : 0)+1;
        root.emplace_back(merge(rtL,rtR));
        return ans;
    }

public:
    T NotFind;
    FHQ_Treap(): root(1,nullptr), NotFind(1919810LL*rng()%int(1e9+7)) {}
    void insert(int version, T val) { // 在第version个版本上操作
        auto [rtL,rtR]=split(root[version],val);
        auto [lsL,lsR]=split(rtL,val-1);
        Node *tt;
        if(lsR==nullptr) tt=new Node(val);
        else{ ++lsR->cnt; lsR->update_siz(); }
        Node *new_rtL=merge(lsL,lsR? lsR:tt);
        root.emplace_back(merge(new_rtL,rtR));
    }

    void del(int version, T val) {
        auto [rtL,rtR]=split(root[version],val);
        auto [lsL,lsR]=split(rtL,val-1);
        if (lsR) {
            if (lsR->cnt > 1) {
                --lsR->cnt;
                lsR->update_siz();
                lsL = merge(lsL, lsR);
            } else {
                if (rtL == lsR) rtL = nullptr;
                delete lsR; lsR = nullptr;
            }
        }
        root.emplace_back(merge(lsL,rtR));
    }


    int queryRank_byVal(int version, T val){ return queryRank(root[version],val); }
    T queryVal_byRank(int version, int rank){ return queryVal(root[version],rank,true); }

    T queryPre(int version, T val) { // 查询x的前驱(小于x的最大的值)
        auto [rtL,rtR]=split(root[version],val-1);
        T ans=rtL? queryVal(rtL,rtL->siz,false):NotFind;
        root.emplace_back(merge(rtL,rtR));
        return ans;
    }

    T queryNxt(int version, T val){ // 查询x的后继(大于x的最小的值)
        auto [rtL,rtR]=split(root[version],val);
        T ans=rtR? queryVal(rtR,1,false):NotFind;
        root.emplace_back(merge(rtL,rtR));
        return ans;
    }
    
    #undef ls
    #undef rs
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; std::cin>>n;
    FHQ_Treap<int>TP;
    while(n--){
        int v,opt,x; std::cin>>v>>opt>>x;
        switch(opt){
        case 1: TP.insert(v,x); break;
        case 2: TP.del(v,x); break;
        case 3: std::cout<<TP.queryRank_byVal(v,x)<<"\n"; break;
        case 4: std::cout<<TP.queryVal_byRank(v,x)<<"\n"; break;
        case 5:{
                int ans=TP.queryPre(v,x);
                std::cout<<(ans==TP.NotFind? 1-(1LL<<31):ans)<<"\n";
                break;
            }
        case 6:{
                int ans=TP.queryNxt(v,x);
                std::cout<<(ans==TP.NotFind? (1LL<<31)-1:ans)<<"\n";
                break;
            }
        }
    }
    return 0;
}



/***
 * @brief   支持可持久化操作的文艺平衡树
*/
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class FHQ_Treap{
private:
    #define ls son[0]
    #define rs son[1]
    struct Node{
        Node *son[2]; // son[0]:ls, son[1]:rs
        T val, sum;
        int rank,siz,tag;
        Node()=default;
        Node(const T v_): val(v_), sum(v_), siz(1), tag(0) {
            son[0]=son[1]=nullptr;
            rank=rng();
        }
        void push_up(){
            siz=1; sum=val;
            if(ls){ siz+=ls->siz; sum+=ls->sum; }
            if(rs){ siz+=rs->siz; sum+=rs->sum; }
        }
        void push_down(){
            if(!tag) return;
            if(ls){
                Node *tt=new Node(*ls);
                ls=tt;
            }
            if(rs){
                Node *tt=new Node(*rs);
                rs=tt;
            }
            std::swap(ls,rs);
            if(ls) ls->tag^=1;
            if(rs) rs->tag^=1;
            tag=0;
        }
    };
    std::vector<Node*>root;

    std::pair<Node*,Node*> splitSiz(Node *cur, int siz_) { // <=, > 按照树的大小分裂
        if(cur==nullptr) return {nullptr,nullptr};
        cur->push_down();
        Node *newCur=new Node(*cur);
        int ls_siz=newCur->ls? newCur->ls->siz:0;
        if(siz_<=ls_siz){
            auto [lsL,lsR]=splitSiz(newCur->ls,siz_);
            newCur->ls=lsR;
            newCur->push_up();
            return {lsL,newCur};
        }
        else{
            auto [rsL,rsR]=splitSiz(newCur->rs,siz_-ls_siz-1);
            newCur->rs=rsL;
            newCur->push_up();
            return {newCur,rsR};
        }
    }

    Node *merge(Node *u, Node *v) { // 合并u,v并返回父节点
        if(u==nullptr) return v;
        if(v==nullptr) return u;
        u->push_down(); v->push_down();
        Node *cur=new Node;
        if(u->rank < v->rank){ // 小根堆
            *cur=*u;
            cur->rs=merge(cur->rs,v);
        }
        else{
            *cur=*v;
            cur->ls=merge(u,cur->ls);
        }
        cur->push_up();
        return cur;
    }

public:
    FHQ_Treap(): root(1,nullptr) {}

    void insert(int version, int rank, T val) { // 在第rank个后面插入val
        auto [rtL,rtR]=splitSiz(root[version],rank);
        root.emplace_back(merge(merge(rtL,new Node(val)), rtR));
    }

    void del(int version, int rank) {
        auto [rtL,rtR]=splitSiz(root[version],rank);
        auto [lsL,lsR]=splitSiz(rtL,rank-1);
        root.emplace_back(merge(lsL,rtR));
    }

    void rangeReverse(int version, int L, int R) { // 区间翻转
        auto [rtL,rtR]=splitSiz(root[version],L-1);
        auto [rsL,rsR]=splitSiz(rtR,R-L+1);
        rsL->tag^=1;
        root.emplace_back(merge(rtL,merge(rsL,rsR)));
    }

    T rangeQurey(int version, int L, int R) { // 区间查询
        auto [rtL,rtR]=splitSiz(root[version],L-1);
        auto [rsL,rsR]=splitSiz(rtR,R-L+1);
        T ans=rsL->sum;
        root.emplace_back(merge(rtL,merge(rsL,rsR)));
        return ans;
    }

    void inorderTraversal(int version, std::vector<T>&res) { // 中序遍历
        auto dfs=[&](auto self,Node *cur)->void{
            if(cur==nullptr) return;
            cur->push_down();
            self(self,cur->ls);
            res.emplace_back(cur->val);
            self(self,cur->rs);
        };
        dfs(dfs,root[version]);
    }
    
    #undef ls
    #undef rs
};