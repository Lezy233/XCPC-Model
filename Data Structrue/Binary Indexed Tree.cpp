#include<bits/stdc++.h>
using namespace std;

struct BIT{ //Binary indexed tree 树状数组
    int n;
    vector<int> tr;
    BIT(int n): n(n), tr(n+1,0) {}
    constexpr int lowbit(int x) { return x&-x; }
    void modify(int x,int modify_number){
        for(int i=x; i<=n; i+=lowbit(i))
            tr[i]+=modify_number;
    }
    int query(int x){
        int res=0;
        for(int i=x;i;i-=lowbit(i))
            res+=tr[i];
        return res;
    }
    int query(int x,int y){
        return query(y)-query(x);
    }
};

int main()
{
    int n; cin>>n;
    BIT bit(2*n+5);
    
}