/**
 *  @note       Splay，伸展树，在正确操作下均摊复杂度为 O(logn)
 *  @warning    因为Splay的时间复杂度采用势能分析的方法证明，
 *              复杂度正确的关键在于每次操作结束对于当前的操作对象使使用splay操作
*/

#include <bits/stdc++.h>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int main() { // 目录
    Splay<int>SP;
    range_Splay<int>rSP(10086);
}

/**
 * @brief   基础Splay, 支持常规平衡树操作
*/
template <typename T>
class Splay {
private:
    #define ls son[0]
    #define rs son[1]
    struct Node{
        Node *fa, *son[2]; // son[0]:ls, son[1]:rs
        T val;
        int siz,cnt;
        Node(){}
        Node(T val_, Node* pre): val(val_), siz(1), cnt(1) {
            ls=rs=nullptr;
            fa=pre;
        }
        int pos(){ return fa->rs==this; } // 查询当前节点是父节点的左节点(0)还是右节点(1)
        void update_siz(){
            siz=cnt;
            if(ls) siz+=ls->siz;
            if(rs) siz+=rs->siz;
        }
    };
    Node *root;

    void rotate(Node *rt) {
        Node *preRt=rt->fa, *pre2Rt=preRt->fa;
        int dirRt=rt->pos(), dirRt2=pre2Rt? preRt->pos():2;
        preRt->son[dirRt]=rt->son[!dirRt];
        if(preRt->son[dirRt]) preRt->son[dirRt]->fa=preRt;
        rt->son[!dirRt]=preRt; preRt->fa=rt;
        rt->fa=pre2Rt;
        if(pre2Rt) pre2Rt->son[dirRt2]=rt;
        preRt->update_siz();
        rt->update_siz();
    }

    void splay(Node *rt){ // 将当前节点旋转至根节点
        for(Node *preRt=nullptr; (preRt=rt->fa)!=nullptr; rotate(rt))
            if(preRt->fa) rotate(preRt->pos()==rt->pos()? preRt:rt);
        root=rt;
    }

public:
    T NotFind;
    Splay(): NotFind(1919810LL*rng()%1'000'000'007) {};
    void insert(T val) {
        if(root==nullptr){
            root=new Node(val,nullptr); return;
        }
        Node *cur=root, *preCur=nullptr;
        while(true){
            if(val==cur->val){
                ++cur->cnt;
                splay(cur);
                return;
            }
            preCur=cur;
            cur=cur->son[val>cur->val];
            if(cur==nullptr){
                preCur->son[val>preCur->val]=cur=new Node(val,preCur);
                splay(cur);
                return;
            }
        }
    }

    int queryRank_byVal(T val) { // 根据值查询排名
        Node *cur=root;
        int ans=1;
        while(true){
            if(cur==nullptr) break;
            if(val<cur->val){
                if(cur->ls) cur=cur->ls;
                else{
                    splay(cur);
                    break;
                }
            }
            else{
                ans+=cur->ls? cur->ls->siz:0;
                if(val==cur->val){
                    splay(cur);
                    break;
                }
                ans+=cur->cnt;
                cur=cur->rs;
            }
        }
        return ans;
    }

    T queryVal_byRank(int rank){ // 根据排名查询值
        Node *cur=root;
        while(true){
            int ls_siz=cur->ls? cur->ls->siz:0;
            if(rank<=ls_siz) cur=cur->ls;
            else if(rank<=ls_siz+cur->cnt) break;
            else{
                rank-=ls_siz+cur->cnt;
                cur=cur->rs;
            }
        }
        splay(cur);
        return cur->val;
    }

    T queryPre(T val){ // 查询前驱(小于val的最大的值)
        T ans=NotFind;
        Node *cur, *nxt=root;
        while(nxt){
            if(cur=nxt; nxt->val>=val) nxt=nxt->ls;
            else ans=nxt->val, nxt=nxt->rs;
        }
        splay(cur);
        return ans;
    }

    T queryNxt(T val){ // 查询后继(大于val的最小的值)
        T ans=NotFind;
        Node *cur, *nxt=root;
        while(nxt){
            if(cur=nxt; nxt->val<=val) nxt=nxt->rs;
            else ans=nxt->val, nxt=nxt->ls;
        }
        splay(cur);
        return ans;
    }

    void del(T val) {
        queryRank_byVal(val);
        if(root->val!=val) return;
        if(root->cnt>1){
            --root->siz; --root->cnt;
            return;
        }
        if(root->ls&&root->rs){
            Node *oldRoot=root;
            queryVal_byRank(root->ls->siz);
            root->rs=oldRoot->rs; root->rs->fa=root;
            delete oldRoot; oldRoot=nullptr;
            root->update_siz();
        }
        else if(root->ls){
            root=root->ls;
            delete root->fa; root->fa=nullptr;
        }
        else if(root->rs){
            root=root->rs;
            delete root->fa; root->fa=nullptr;
        }
        else{
            delete root; root=nullptr;
        }
    }
    
    #undef ls
    #undef rs
};

/**
 * @brief   支持旋转的Splay
*/
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template <typename T>
class range_Splay {
private:
    #define ls son[0]
    #define rs son[1]
    struct Node{
        Node *fa, *son[2]; // son[0]:ls, son[1]:rs
        T val;
        int siz,cnt,tag;
        Node(){}
        Node(T val_, Node* pre): val(val_), siz(1), cnt(1), tag(0) {
            ls=rs=nullptr;
            fa=pre;
        }
        int pos(){ return fa->rs==this; } // 查询当前节点是父节点的左节点(0)还是右节点(1)
        void push_down() {
            if(tag){
                if(ls) ls->tag^=1;
                if(rs) rs->tag^=1;
                std::swap(ls,rs);
                tag=0;
            }
        }
        void push_up(){
            siz=cnt;
            if(ls) siz+=ls->siz;
            if(rs) siz+=rs->siz;
        }
    };
    Node *root;

    void rotate(Node *rt) {
        Node *preRt=rt->fa, *pre2Rt=preRt->fa;
        preRt->push_down();
        rt->push_down();
        int dirRt=rt->pos(), dirRt2=pre2Rt? preRt->pos():2;
        preRt->son[dirRt]=rt->son[!dirRt];
        if(preRt->son[dirRt]) preRt->son[dirRt]->fa=preRt;
        rt->son[!dirRt]=preRt; preRt->fa=rt;
        rt->fa=pre2Rt;
        if(pre2Rt) pre2Rt->son[dirRt2]=rt;
        preRt->push_up();
        rt->push_up();
    }

    void splay(Node *rt){ // 将当前节点旋转至根节点
        for(Node *preRt=nullptr; (preRt=rt->fa)!=nullptr; rotate(rt))
            if(preRt->fa) rotate(preRt->pos()==rt->pos()? preRt:rt);
        root=rt;
    }

    void splay(Node *cur, Node *tar) { // 将当前节点旋转至tar的儿子
        for(Node *preCur=nullptr; (preCur=cur->fa)!=tar; rotate(cur))
            if(preCur->fa!=tar) rotate(preCur->pos()==cur->pos()? preCur:cur);
    }

public:
    T NotFind;
    range_Splay(): root(nullptr), NotFind(1919810LL*rng()%1'000'000'007) {};
    range_Splay(int n): root(nullptr), NotFind(1919810LL*rng()%1'000'000'007) { // 此时Splay用于区间翻转
        for(int i=0;i<=n+1;++i) insert(i);
    };

    void insert(T val) {
        if(root==nullptr){
            root=new Node(val,nullptr); return;
        }
        Node *cur=root, *preCur=nullptr;
        while(true){
            if(val==cur->val){
                ++cur->cnt;
                splay(cur);
                return;
            }
            preCur=cur;
            cur=cur->son[val>cur->val];
            if(cur==nullptr){
                preCur->son[val>preCur->val]=cur=new Node(val,preCur);
                splay(cur);
                return;
            }
        }
    }

    int queryRank_byVal(T val) { // 根据值查询排名
        Node *cur=root;
        int ans=1;
        while(true){
            if(cur==nullptr) break;
            if(val<cur->val){
                if(cur->ls) cur=cur->ls;
                else{
                    splay(cur);
                    break;
                }
            }
            else{
                ans+=cur->ls? cur->ls->siz:0;
                if(val==cur->val){
                    splay(cur);
                    break;
                }
                ans+=cur->cnt;
                cur=cur->rs;
            }
        }
        return ans;
    }

    T queryVal_byRank(int rank){ // 根据排名查询值
        Node *cur=root;
        while(true){
            cur->push_down();
            int ls_siz=cur->ls? cur->ls->siz:0;
            if(rank<=ls_siz) cur=cur->ls;
            else if(rank<=ls_siz+cur->cnt) break;
            else{
                rank-=ls_siz+cur->cnt;
                cur=cur->rs;
            }
        }
        splay(cur);
        return cur->val;
    }

    T queryPre(T val){ // 查询前驱(小于val的最大的值)
        T ans=NotFind;
        Node *cur, *nxt=root;
        while(nxt){
            if(cur=nxt; nxt->val>=val) nxt=nxt->ls;
            else ans=nxt->val, nxt=nxt->rs;
        }
        splay(cur);
        return ans;
    }

    T queryNxt(T val){ // 查询后继(大于val的最小的值)
        T ans=NotFind;
        Node *cur, *nxt=root;
        while(nxt){
            if(cur=nxt; nxt->val<=val) nxt=nxt->rs;
            else ans=nxt->val, nxt=nxt->ls;
        }
        splay(cur);
        return ans;
    }

    void del(T val) {
        queryRank_byVal(val);
        if(root->val!=val) return;
        if(root->cnt>1){
            --root->siz; --root->cnt;
            return;
        }
        if(root->ls&&root->rs){
            Node *oldRoot=root;
            queryVal_byRank(root->ls->siz);
            root->rs=oldRoot->rs; root->rs->fa=root;
            delete oldRoot; oldRoot=nullptr;
            root->push_up();
        }
        else if(root->ls){
            root=root->ls;
            delete root->fa; root->fa=nullptr;
        }
        else if(root->rs){
            root=root->rs;
            delete root->fa; root->fa=nullptr;
        }
        else{
            delete root; root=nullptr;
        }
    }

    void rangeReverse(int L,int R) {
        queryVal_byRank(R+2);
        Node *tt=root;
        queryVal_byRank(L);
        splay(tt,root);
        root->rs->ls->tag^=1;
    }

    void inorderTraversal(std::vector<T>&res) {
        auto dfs=[&](auto self,Node *cur)->void{
            if(cur==nullptr) return;
            cur->push_down();
            self(self,cur->ls);
            res.emplace_back(cur->val);
            self(self,cur->rs);
        };
        dfs(dfs,root);
    }

    #undef ls
    #undef rs
};

/* 
// 以下为 Luogu P6136代码
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m; std::cin>>n>>m;
    Splay<int>SP;
    while(n--){
        int tt; std::cin>>tt;
        SP.insert(tt);
    }
    int res=0, last=0;
    while(m--){
        int opt,x; cin>>opt>>x; x^=last;
        switch(opt){
        case 1: SP.insert(x); break;
        case 2: SP.del(x); break;
        case 3: res^=(last=SP.queryRank_byVal(x)); break;
        case 4: res^=(last=SP.queryVal_byRank(x)); break;
        case 5: res^=(last=SP.queryPre(x)); break;
        case 6: res^=(last=SP.queryNxt(x)); break;
        }
    }
    std::cout<<res<<"\n";
    return 0;
} 
*/