/**
 * @brief   求平面中两点的最近距离，采用分治的思想（其实和平面几何没有什么关系
 *          刚好和旋转卡壳相反
*/

// P1429

#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef long long ll;

const double EPS=1e-9; // 精度
const double PI=acos(-1);
struct Point { double x, y; };

double dis(Point A, Point B){ return hypot(A.x-B.x,A.y-B.y); }      //  两点之间距离
double dis(Point P, Line L){ return std::fabs((P^L.v)-(L.P^L.v)/len(L.v)); } // 点到直线距离

bool const operator<(const Point&a,const Point b) {
    return a.x<b.x || a.x==b.x&&a.y<b.y;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin>>n;
    vector<Point>aa(n);
    for(auto &[x,y]:aa) cin>>x>>y;
    std::ranges::sort(aa);

    auto solve=[&](auto self,int rtL,int rtR)->double{ // [rtL,rtR)
        if(rtL==rtR) return 1e10;
        if(rtR-rtL==1) return dis(aa[rtL],aa[rtR]);
        int mid=rtL+rtR>>1;
        double r=std::min(self(self,rtL,mid), self(self,mid,rtR));
        auto L=std::lower_bound(aa.begin()+rtL,aa.begin()+mid,Point(aa[mid].x-r,-1e7));
        auto R=std::lower_bound(aa.begin()+mid,aa.begin()+rtR+1,Point(aa[mid].x+r,-1e7));
        vector<Point>tt(L,R);
        std::ranges::sort(tt,[](const Point&a,const Point&b){
           return a.y<b.y || a.y==b.y&&a.x<b.x;
        });
        for(int i=0,j=1,m=tt.size();i<m;++i){
            while(j<m && tt[j].y-tt[i].y<r) ++j;
            for(int k=i+1;k<j;++k) r=std::min(r, dis(tt[i],tt[k]));
        }
        return r;
    };
    double minDis=solve(solve,0,n-1);
    cout<<std::fixed<<std::setprecision(7)<<minDis<<endl;
    return 0;
}