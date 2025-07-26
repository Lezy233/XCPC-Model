/**
 * @brief   最普通的线段树，适合搭配一些其他知识点使用（如动态开点、可持久化）
*/
#include <bits/stdc++.h>

const int N=1e3+5;
const int INF=0x3f3f3f3f;
int tree[N*4]={0};
int tag[N<<2]={0};
inline int ls(int p){return p<<1;} // 左子结点
inline int rs(int p){return p<<1|1;} // 右子结点
void push_up(int p){ // 从下往上传递区间值
    tree[p]=tree[ls(p)]+tree[rs(p)];
    // tree[p]=max(tree[ls(p)],tree[rs(p)]);
}
void addtag(int p,int pl,int pr,int d){
    tag[p]+=d;
    tree[p]+=d*(pr-pl+1);
}
void push_down(int p,int pl,int pr){ // 从上往下传递tag
    if(tag[p]){
        int mid=(pl+pr)>>1;
        addtag(ls(p),pl,mid,tag[p]);
        addtag(rs(p),mid+1,pr,tag[p]);
        tag[p]=0;
    }
}
void build(int p,int pl,int pr){ // p父节点,pl pr子结点
    if(pl==pr){ // 到达最底层的叶子结点，存叶子的值
        tree[p]=-INF;
        return;
    }
    int mid=(pl+pr)>>1; // 分治折半
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    push_up(p);
}
void update(int p,int pl,int pr,int L,int R,int d){ // 区间修改，更新[L,R]的区间和
    if(L<=pl&&pr<=R){
        tree[p]=d;
        return;
    }
    int mid=(pl+pr)>>1;
    if(L<=mid) update(ls(p),pl,mid,L,R,d);
    if(R>mid) update(rs(p),mid+1,pr,L,R,d);
    push_up(p);
    return;
}
int query(int p,int pl,int pr,int L,int R) { // 查询[L,R]的区间和
    int res=0;
    if(L<=pl&&pr<=R) return tree[p]; // 完全覆盖
    int mid=(pl+pr)>>1;
    if(L<=mid) res+=query(ls(p),pl,mid,L,R); // L与左部分有重叠
    //if(L<=mid)res=max(res,query(ls(p),pl,mid,L,R));
    if(R>mid) res+=query(rs(p),mid+1,pr,L,R); // R与右部分有重叠
    //if(R>mid)res=max(res,query(rs(p),mid+1,pr,L,R));
    return res;
}

int main()
{
    int t=0,cnt=0,m,D;
    std::cin>>m>>D;
    build(1,1,N); // update(1,1,N,1,N,-INFINITY);
    return 0;
}