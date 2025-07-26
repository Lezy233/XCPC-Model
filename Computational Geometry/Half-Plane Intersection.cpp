/**
 * @brief   Half-Plane Intersection  半平面交
 * @note    如果题目没有强调最终必定得到一个封闭图形，可以通过加一个极大的外边框
*/
// P4196
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"

const double EPS=1e-8; // 精度
const double PI=acos(-1);
struct Point { double x, y; };
using Vec=Point;
struct Line { Point P; Vec v; };        // 直线 (点向式)
struct Seg { Point A, B; };             // 线段
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
double toArc(double x) { return PI*x/180.0; }                       //  角度转弧度
Vec norm(Vec v){ return {v.x/len(v), v.y/len(v)}; }                 //  向量归一化
Vec pnorm(Vec v){ return (v.x<0?-1:1)/len(v)*v; }                   //  指向x轴正半轴的归一化向量

double theta(Point A){ return atan2(A.y,A.x); }                     //  求点的极角

double dis(Point A, Point B){ return hypot(A.x-B.x,A.y-B.y); }      //  两点之间距离

Point rotate(Point P, double rad){                                  //  P点绕原点逆时针旋转
    return {cos(rad)*P.x-sin(rad)*P.y, sin(rad)*P.x+cos(rad)*P.y};
}

Line line(Point A, Point B) { return {A,B-A}; }                     //  直线（两点式）

bool p2lineR(Point P, Line l){ return ge((P-l.P)^l.v,0); }          //  判断点是否在向量的右侧

Point inter(Line a, Line b) { // 求两直线交点                        //  求两直线交点
    double c=a.v^b.v;
    if(eq(c,0)) return {};
    Vec v=1/c * Vec(a.P^(a.P+a.v), b.P^(b.P+b.v));
    return Point(v*Vec(-b.v.x, a.v.x), v*Vec(-b.v.y, a.v.y));
}

double polyArea(const std::vector<Point>&ps) {  // 多边形面积       //  多边形面积
    double ans=ps.back()^ps.front();
    for(int i=1;i<ps.size();++i) ans+=ps[i-1]^ps[i];
    return ans/2;
}

void HPI(std::vector<Line>&lies, std::vector<Point>&ps) {
    std::ranges::sort(lies,[&](const Line&x,const Line&y){
        if(double tx=theta(x.v), ty=theta(y.v); !eq(tx,ty)) return lt(tx,ty);
        return gt(x.v^(x.P-y.P),0);
    });

    int tot=1;
    for(int i=1;i<lies.size();++i)
        if(!eq(theta(lies[i-1].v),theta(lies[i].v))) lies[tot++]=lies[i];
    lies.resize(tot);
    
    std::vector<Line>dq; // 使用vector模仿deque
    int L=0, R=-1;
    for(auto &i:lies){
        while(L<R&&p2lineR(inter(dq[R-1],dq[R]),i)) --R;
        while(L<R&&p2lineR(inter(dq[L],dq[L+1]),i)) ++L;
        if(++R>=dq.size()) dq.emplace_back(i);
        else dq[R]=i;
    }
    while(L<R&&p2lineR(inter(dq[R-1],dq[R]),dq[L])) --R;
    while(L<R&&p2lineR(inter(dq[L],dq[L+1]),dq[R])) ++L;

    // 如果是判断有无合法的点，改成
    // return R-L+1>=3;
    ps.emplace_back(inter(dq[R],dq[L]));
    for(int i=L+1;i<=R;++i) ps.emplace_back(inter(dq[i-1],dq[i]));
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin>>n;
    vector<Line>lies;
    while(n--){
        int m; cin>>m;
        vector<Point>aa(m);
        for(auto &[x,y]:aa){
            int xx,yy; cin>>xx>>yy;
            x=xx, y=yy;
        }
        for(int i=0;i<m;++i) lies.emplace_back(line(aa[i],aa[(i+1)%m]));
    }

    vector<Point>ps;
    HPI(lies,ps);
    cout<<std::fixed<<std::setprecision(3)<<polyArea(ps)<<endl;
    return 0;
}