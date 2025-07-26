// @note    min Cover Circle  最小覆盖圆
// P1742
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef long long ll;
typedef std::tuple<ll,ll,ll> T3L;

#define double long double

const double EPS=1e-15; // 精度
const double PI=acos(-1);
struct Point { double x, y; };
using Vec=Point;
struct Line { Point P; Vec v; };        // 直线 (点向式)
struct Seg { Point A,B; };              // 线段
struct Circle { Point O; double r; };   // 圆

const Point O={0,0};

// 浮点数比较（考虑到精度）
bool eq(double a, double b){ return std::fabs(a-b)<EPS; }   // ==   //  ==
bool gt(double a, double b){ return a-b>EPS; }              // >    //  >
bool lt(double a, double b){ return a-b<-EPS; }             // <    //  <
bool ge(double a, double b){ return a-b>-EPS; }             // >=   //  >=
bool le(double a, double b){ return a-b<EPS; }              // <=   //  <=

Vec r90a(Vec v) { return {-v.y, v.x}; }                             //  逆时针旋转90度的向量
Vec r90c(Vec v) { return {v.y, -v.x}; }                             //  顺时针旋转90度的向量
Vec operator+(Vec u, Vec v) { return {u.x + v.x, u.y + v.y}; }      //  向量加向量
Vec operator-(Vec u, Vec v) { return {u.x - v.x, u.y - v.y}; }      //  向量减向量
Vec operator*(double k, Vec v) { return {k * v.x, k * v.y}; }       //  数乘
Vec operator*(Vec v, double k) { return {k * v.x, k * v.y}; }       //  数乘（两个方向）
double operator*(Vec u, Vec v) { return u.x * v.x + u.y * v.y; }    //  点乘
double operator^(Vec u, Vec v) { return u.x * v.y - u.y * v.x; }    //  叉乘
double len(Vec v) { return sqrt(v.x * v.x + v.y * v.y); }           //  向量长度
double toArc(double x){ return PI*x/180.0; }                        //  角度转弧度

double dis(Point A, Point B){ return hypot(A.x-B.x,A.y-B.y); }      //  两点之间距离

Point circumcenter(Point A, Point B, Point C) { // 三角形外心       //  三角形外心
    double a=A*A, b=B*B, c=C*C;
    double d=2*(A.x*(B.y-C.y)+B.x*(C.y-A.y)+C.x*(A.y-B.y));
    return 1/d*r90c(a*(B-C)+b*(C-A)+c*(A-B));
}

Circle min_Cover_Circle(std::vector<Point>&ps) {
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::ranges::shuffle(ps,rng);
    Point C=ps[0]; double r=0;
    for(int i=1;i<ps.size();++i){
        if(le(dis(ps[i],C),r)) continue; // 点在圆内部
        C=ps[i]; r=0;
        for(int j=0;j<i;++j){
            if(le(dis(ps[j],C),r)) continue;
            C=0.5*(ps[i]+ps[j]);
            r=dis(ps[i],C);
            for(int k=0;k<j;++k) if(gt(dis(ps[k],C),r)){
                C=circumcenter(ps[i],ps[j],ps[k]);
                r=dis(ps[i],C);
            }
        }
    }
    return {C,r};
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin>>n;
    vector<Point>aa(n);
    for(auto &[x,y]:aa) cin>>x>>y;
    auto res=min_Cover_Circle(aa);
    cout<<std::fixed<<std::setprecision(12)<<res.r<<endl<<res.O.x<<" "<<res.O.y<<endl;
    return 0;
}