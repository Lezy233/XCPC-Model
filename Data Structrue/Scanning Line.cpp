// P8648 AC / P5490 AC
#include <bits/stdc++.h>
#include <bits/extc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef long long ll;
typedef std::tuple<ll,ll,ll,ll> T4L;

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin>>n;
    vector<T4L>line;
    vector<ll>alls; // 记录y
    for(int i=0;i<n;++i){
        ll x1,y1,x2,y2; cin>>x1>>y1>>x2>>y2;
        if(x1>x2) std::swap(x1,x2);
        if(y1>y2) std::swap(y1,y2);
        alls.emplace_back(y1), alls.emplace_back(y2);
        line.emplace_back(x1,y1,y2,1); // 入边
        line.emplace_back(x2,y1,y2,-1); // 出边
    }
    std::ranges::sort(line);

    std::ranges::sort(alls);
    alls.erase(std::unique(alls.begin(),alls.end()),alls.end());
    __gnu_pbds::gp_hash_table<ll,int>mp;
    for(int i=0;i<alls.size();++i) mp[alls[i]]=i;
    
    vector<int>tag(alls.size()<<2);
    vector<ll>len(alls.size()<<2); // len表示的是当前该点覆盖的面积

    auto push_up=[&](int rt,int rtL,int rtR)->void{ // 区间左闭右开
        if(tag[rt]) len[rt]=alls[rtR]-alls[rtL];
        else if(rtR-rtL==1) len[rt]=0; // 子节点,并且没有tag,长度为0
        else len[rt]=len[rt<<1]+len[rt<<1|1];
    };

    auto rangeUpdate=[&](auto self,int rt,int rtL,int rtR,int L,int R,int d)->void{
        // rtL,rtR: rt覆盖的区间;    L,R: 当前修改的区间
        if(L>rtR||R<rtL) return;
        if(L<=rtL&&R>=rtR){
            tag[rt]+=d;
            push_up(rt,rtL,rtR);
            return;
        }
        if(rtL+1>=rtR) return;
        int mid=rtL+rtR>>1;
        if(L<=mid) self(self,rt<<1,rtL,mid,L,R,d);
        if(R>mid) self(self,rt<<1|1,mid,rtR,L,R,d);
        push_up(rt,rtL,rtR);
    };

    ll res=0;
    for(int i=0;i<n*2;++i){
        if(i) res+=len[1]*(get<0>(line[i])-get<0>(line[i-1]));
        rangeUpdate(rangeUpdate,1,0,alls.size()-1,mp[get<1>(line[i])],mp[get<2>(line[i])],get<3>(line[i]));
    }
    cout<<res<<endl;
    return 0;
}
