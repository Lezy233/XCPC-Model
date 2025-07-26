// P4097 AC
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef long long ll;

const int MOD1=39989, MOD2=1e9;

// 李超线段树维护每个区间中完全通过该区间，且位于最上层的线段
// 采用了标记永久化

class LiChao_SegmentTree {
private:
    #define ls (rt<<1)
    #define rs (rt<<1|1)
    #define mid (rtL+rtR>>1)
    #define _mid (_rtL+_rtR>>1)
    using PDI = std::pair<double,int>;
    struct Line {
        double k,b; // y=k*x+b
    };
    int INF;
    std::vector<Line> line;
    std::vector<int> id;
    double calc(int id,double x) {
        return line[id].k*x+line[id].b;
    }

    const double EPS = 1e-9;
    PDI pMax(PDI x,PDI y) {
        if(x.first-y.first>EPS) return x;
        if(y.first-x.first>EPS) return y;
        return x.second<y.second? x:y;
    }
    
    void update(int rt,int rtL,int rtR,int L,int R,int u) {
        auto upd = [&](auto self,int _rt,int _rtL,int _rtR,int _u)->void {
            auto &_v=id[_rt];
            if(double um=calc(_u,_mid), vm=calc(_v,_mid); um-vm>EPS||(std::abs(um-vm)<=EPS&&_u<_v)) std::swap(_u,_v);
            if(double ul=calc(_u,_rtL), vl=calc(_v,_rtL); ul-vl>EPS||(std::abs(ul-vl)<=EPS&&_u<_v))
                self(self,_rt<<1,_rtL,_mid,_u);
            if(double ur=calc(_u,_rtR), vr=calc(_v,_rtR); ur-vr>EPS||(std::abs(ur-vr)<=EPS&&_u<_v))
                self(self,_rt<<1|1,_mid+1,_rtR,_u);
        };

        if(L<=rtL&&rtR<=R){ upd(upd,rt,rtL,rtR,u); return; }
        if(L<=mid) update(ls,rtL,mid,L,R,u);
        if(R>mid) update(rs,mid+1,rtR,L,R,u);
    }

    PDI query(int rt,int L,int R,int x) {
        if(R<x||x<L) return {0,0};
        double res=calc(id[rt],x);
        if(L==R) return {res,id[rt]};
        return pMax({res,id[rt]}, pMax(query(ls,L,L+R>>1,x),query(rs,(L+R)/2+1,R,x)) );
    }
public:
    // @param: _n: num of segment; _MOD: right border
    LiChao_SegmentTree(int _n, int _MOD): id(_n<<2), INF(_MOD) {
        line.emplace_back(Line());
    };
    
    void addLine(int x0,int y0,int x1,int y1) {
        if(x0==x1) line.emplace_back(0,std::max(y0,y1));
        else{
            if(x0>x1) std::swap(x0,x1), std::swap(y0,y1);
            double k=1.0*(y1-y0)/(x1-x0);
            line.emplace_back(k, y0-k*x0);
        }
        update(1,1,INF,x0,x1,line.size()-1);
    }

    PDI query(int x) { // [L,R] 查询区间
        return query(1,1,INF,x);
    }
    #undef ls
    #undef rs
    #undef mid
    #undef _mid
};


int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int q, lastans=0; cin>>q;
    LiChao_SegmentTree LST(1e5,MOD1);
    for(int id=1;id<=q;++id){
        int opt; cin>>opt;
        if(opt){
            int x0,y0,x1,y1; cin>>x0>>y0>>x1>>y1;
            x0=(x0+lastans-1)%MOD1+1, x1=(x1+lastans-1)%MOD1+1;
            y0=(y0+lastans-1)%MOD2+1, y1=(y1+lastans-1)%MOD2+1;
            LST.addLine(x0,y0,x1,y1);
        }            
        else{
            int k; cin>>k;
            k=(k+lastans-1)%MOD1+1;
            lastans=LST.query(k).second;
            cout<<lastans<<endl;
        }
    }
    return 0;
}