/**
 *  @note   Treap Tree+Heap 树堆
*/

#include <bits/stdc++.h>

int main(){
    // 目录
    Treap<int>TP1; // 带旋Treap
    FHQ_Treap<int>TP2; // 无旋Treap
}

// 带旋Treap, 使用指针实现
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class Treap{
private:
    #define ls son[0]
    #define rs son[1]
    struct Node{
        Node *son[2]; // son[0]:ls, son[1]:rs
        T val;
        int rank,cnt,siz;
        Node(T _val): val(_val), cnt(1), siz(1) {
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
    
    enum rot_type{LF=1, RT=0};
    void rotate(Node *&rt, rot_type dir) { // dir旋转方向, 0->right rotate, 1->left rotate
        Node *tt=rt->son[dir];
        rt->son[dir]=tt->son[!dir];
        tt->son[!dir]=rt;
        tt->update_siz(), rt->update_siz();
        rt=tt;
    }
    void _insert(Node *&cur, T v_) {
        if(cur==nullptr){ cur=new Node(v_); return; }
        if(v_==cur->val){
            ++cur->cnt; ++cur->siz;
        }
        else if(v_ < cur->val){ // 小根堆
            _insert(cur->ls,v_);
            if(cur->ls->rank < cur->rank) rotate(cur,RT);
            cur->update_siz();
        }
        else{
            _insert(cur->rs,v_);
            if(cur->rs->rank < cur->rank) rotate(cur,LF);
            cur->update_siz();
        }
    }

    void _del(Node *&cur, T v_) {
        if(cur==nullptr) return;
        if(v_ < cur->val){ _del(cur->ls,v_); cur->update_siz(); }
        else if(v_ > cur->val){ _del(cur->rs,v_); cur->update_siz(); }
        else{
            if(cur->cnt > 1){
                --cur->siz, --cur->cnt;
                return;
            }
            Node *tt=cur;
            if(cur->ls&&cur->rs){
                rot_type dir=cur->ls->rank < cur->rs->rank? RT:LF; // 此处dir是rank更小的那个儿子
                rotate(cur,dir); // 此时cur变为优先级更小的儿子
                _del(cur->son[!dir],v_);
                cur->update_siz();
            }
            else if(cur->ls){
                cur=tt->ls;
                delete tt; tt=nullptr;
            }
            else if(cur->rs){
                cur=tt->rs;
                delete tt; tt=nullptr;
            }
            else{
                delete cur; cur=nullptr;
            }

        }
    }

    int _queryRank(Node *cur, T v_) { // 根据值查询排名
        int ls_siz=cur->ls? cur->ls->siz:0;
        if(v_==cur->val) return ls_siz+1;
        if(v_ < cur->val){
            if(cur->ls) return _queryRank(cur->ls,v_);
            return 1;
        }
        else{
            if(cur->rs) return ls_siz+cur->cnt+_queryRank(cur->rs,v_);
            return cur->siz+1;
        }
    }

    T _queryVal(Node *cur, int rank_) { // 根据排名查询值
        int ls_siz=cur->ls? cur->ls->siz:0;
        if(rank_<=ls_siz) return _queryVal(cur->ls,rank_);
        if(rank_<=ls_siz+cur->cnt) return cur->val;
        return _queryVal(cur->rs,rank_-ls_siz-cur->cnt);
    }

    T _queryPre(Node *cur, T v_) { // 查询x的前驱(小于x的最大的值)
        if(v_ <= cur->val) return cur->ls? _queryPre(cur->ls,v_):NotFind;
        T tt=NotFind;
        if(cur->rs) tt=_queryPre(cur->rs,v_);
        return tt==NotFind? cur->val:tt;
    }

    T _queryNxt(Node *cur, T v_) { // 查询x的后继(大于x的最小的值)
        if(v_ >= cur->val) return cur->rs? _queryNxt(cur->rs,v_):NotFind;
        T tt=NotFind;
        if(cur->ls) tt=_queryNxt(cur->ls,v_);
        return tt==NotFind? cur->val:tt;
    }
public:
    T NotFind;
    Treap(): NotFind(1919810LL*rng()%int(1e9+7)) {}
    void insert(T val){ _insert(root, val); }
    void del(T val){ _del(root, val); }
    int queryRank_byVal(T val){ return _queryRank(root, val); }
    T queryVal_byRank(int rank){ return _queryVal(root, rank); }
    T queryPre(T val){ return _queryPre(root, val); }
    T queryNxt(T val){ return _queryNxt(root, val); }
    #undef ls
    #undef rs
};

// ------------------------------------------------------------

// 无旋Treap, 又称FHQ-Treap

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
        ~Node(){ delete ls; delete rs; }
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

    Node *merge(Node *u, Node *v) { // 合并u,v并返回父节点
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

    int queryRank(Node *cur, T v_) { // 根据值查询排名
        auto [rtL,rtR]=split(cur,v_-1);
        int ans=(rtL? rtL->siz:0)+1;
        root=merge(rtL,rtR);
        return ans;
    }

public:
    FHQ_Treap(): root(nullptr) {}
    void insert(T val) {
        auto [rtL,rtR]=split(root,val);
        auto [lsL,lsR]=split(rtL,val-1);
        Node *tt;
        if(lsR==nullptr) tt=new Node(val);
        else{ ++lsR->cnt; lsR->update_siz(); }
        Node *new_rtL=merge(lsL,lsR? lsR:tt);
        root=merge(new_rtL,rtR);
    }

    void del(T val, int val_cnt=1) {
        auto [rtL,rtR]=split(root,val);
        auto [lsL,lsR]=split(rtL,val-1);
        if(lsR->cnt > val_cnt){
            lsR->cnt -= val_cnt;
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
        T ans=queryVal(rtL,rtL->siz);
        root=merge(rtL,rtR);
        return ans;
    }

    T queryNxt(T val){ // 查询x的后继(大于x的最小的值)
        auto [rtL,rtR]=split(root,val);
        T ans=queryVal(rtR,1);
        root=merge(rtL,rtR);
        return ans;
    }
    
    #undef ls
    #undef rs
};


// ------------------------------------------------------------

/**
 * @brief   Treap 数组实现 常数更小
*/
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N=1e7;

int tot=0;
struct Node{
    int son[2];
    int val;
    int rank,cnt,siz;
    Node(): val(0), cnt(0), siz(0), son(0) {}
    Node(int val_): val(val_), cnt(1), siz(1), son(0), rank(rng()) {}
}tree[N];

template <typename T>
class FHQ_Treap {
private:
    #define ls(cur) tree[cur].son[0]
    #define rs(cur) tree[cur].son[1]

    int root;

    void update_siz(int cur) {
        tree[cur].siz=tree[cur].cnt+tree[ls(cur)].siz+tree[rs(cur)].siz;
    }

    std::pair<int,int> split(int cur, T key) { // split by key  <=, >
        if(cur==0) return {0,0};
        if(tree[cur].val<=key){
            auto [rsL,rsR]=split(rs(cur),key);
            rs(cur)=rsL;
            update_siz(cur);
            return {cur,rsR};
        }
        else{
            auto [lsL,lsR]=split(ls(cur),key);
            ls(cur)=lsR;
            update_siz(cur);
            return {lsL,cur};
        }
    }

    std::tuple<int,int,int> splitRank(int cur, int rank_) {
        if(cur==0) return {0,0,0};
        int ls_siz=tree[ls(cur)].siz;
        int l,mid,r;
        if(rank_<=ls_siz){
            std::tie(l,mid,r)=splitRank(ls(cur),rank_);
            ls(cur)=r;
            update_siz(cur);
            return {l,mid,cur};
        }
        else if(rank_<=ls_siz+tree[cur].cnt){
            l=ls(cur), r=rs(cur);
            ls(cur)=0, rs(cur)=0;
            return {l,cur,r};
        }
        else{
            std::tie(l,mid,r)=splitRank(rs(cur),rank_-ls_siz-tree[cur].cnt);
            rs(cur)=l;
            update_siz(cur);
            return {cur,mid,r};
        }
    }

    int merge(int u, int v) {
        if(!u || !v) return u+v;
        if(tree[u].rank < tree[v].rank){
            rs(u)=merge(rs(u),v); update_siz(u); return u;
        }
        else{
            ls(v)=merge(u,ls(v)); update_siz(v); return v;
        }
    }

    T queryVal(int cur, int rank_) { // 根据排名查询值
        auto [l,mid,r]=splitRank(cur,rank_);
        root=merge(merge(l,mid),r);
        return tree[mid].val;
    }

    int queryRank(int cur, T v_) { // 根据值查询排名
        auto [rtL,rtR]=split(cur,v_-1);
        int ans=tree[rtL].siz+1;
        root=merge(rtL,rtR);
        return ans;
    }

public:
    FHQ_Treap(): root(0) {}

    void insert(T val) {
        auto [rtL,rtR]=split(root,val);
        auto [lsL,lsR]=split(rtL,val-1);
        int tt=lsR;
        if(lsR==0){
            tt=++tot; tree[tot]=Node(val);
        }
        else{
            ++tree[lsR].cnt; update_siz(lsR);
        }
        root=merge(merge(lsL,tt),rtR);
    }

    void del(T val) {
        auto [rtL,rtR]=split(root,val);
        auto [lsL,lsR]=split(rtL,val-1);
        if(tree[lsR].cnt>1){
            --tree[lsR].cnt;
            update_siz(lsR);
            lsL=merge(lsL,lsR);
        }
        else if(rtL==lsR) rtL=0;
        root=merge(lsL,rtR);
    }

    int queryRank_byVal(T val){ return queryRank(root,val); }
    T queryVal_byRank(int rank){ return queryVal(root,rank); }

    T queryPre(T val) { // 查询x的前驱(小于x的最大的值)
        auto [rtL,rtR]=split(root,val-1);
        T ans=rtL? queryVal(rtL,tree[rtL].siz):-2147483647;
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

// ------------------------------------------------------------

// 支持区间翻转操作的 FHQ-Treap

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class FHQ_Treap{
private:
    #define ls son[0]
    #define rs son[1]
    struct Node{
        Node *son[2]; // son[0]:ls, son[1]:rs
        T val;
        int rank,cnt,siz,tag;
        Node(T v_): val(v_), cnt(1), siz(1), tag(0) {
            son[0]=son[1]=nullptr;
            rank=rng();
        }
        void push_up(){
            siz=cnt;
            if(ls) siz+=ls->siz;
            if(rs) siz+=rs->siz;
        }
        void push_down(){
            if(tag){
                std::swap(ls,rs);
                if(ls) ls->tag^=1;
                if(rs) rs->tag^=1;
                tag=0;
            }
        }
    };
    Node *root;

    std::pair<Node*,Node*> splitSiz(Node *cur, int siz_) { // <=, > 按照树的大小分裂
        if(cur==nullptr) return {nullptr,nullptr};
        cur->push_down();
        int ls_siz=cur->ls? cur->ls->siz:0;
        if(siz_<=ls_siz){
            auto [lsL,lsR]=splitSiz(cur->ls,siz_);
            cur->ls=lsR;
            cur->push_up();
            return {lsL,cur};
        }
        else{
            auto [rsL,rsR]=splitSiz(cur->rs,siz_-ls_siz-cur->cnt);
            cur->rs=rsL;
            cur->push_up();
            return {cur,rsR};
        }
    }

    Node *merge(Node *u,Node *v) { // 合并u,v并返回父节点
        if(u==nullptr) return v;
        if(v==nullptr) return u;
        u->push_down(); v->push_down();
        if(u->rank < v->rank){ // 小根堆
            u->rs=merge(u->rs,v); u->push_up(); return u;
        }
        else{
            v->ls=merge(u,v->ls); v->push_up(); return v;
        }
    }

public:
    FHQ_Treap(): root(nullptr) {}
    FHQ_Treap(int n): root(nullptr) {
        for(int i=1;i<=n;++i) insert(i);
    }

    void insert(int rank) {
        auto [rtL,rtR]=splitSiz(root,rank);
        auto [lsL,lsR]=splitSiz(rtL,rank-1);
        Node *tt;
        if(lsR==nullptr) tt=new Node(rank);
        else{ ++lsR->cnt; lsR->push_up(); }
        root=merge(merge(lsL,lsR? lsR:tt), rtR);
    }

    void rangeReverse(int L, int R) { // 区间翻转
        auto [rtL,rtR]=splitSiz(root,L-1);
        auto [rsL,rsR]=splitSiz(rtR,R-L+1);
        rsL->tag^=1;
        root=merge(rtL,merge(rsL,rsR));
    }

    void inorderTraversal(std::vector<T>&res) { // 中序遍历
        auto dfs=[&](auto self,Node *cur)->void{
            if(cur==nullptr) return;
            cur->push_down();
            self(self,cur->ls);
            res.emplace_back(cur->val);
            self(self,cur->rs);
        };
        dfs(dfs,root);
    }
};