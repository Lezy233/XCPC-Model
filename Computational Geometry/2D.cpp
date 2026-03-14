/**
 * @brief   Computational Geometry of two-dimensional
 * @warning WA的时候考虑：1.直线斜率是否存在, 2.精度问题
 * @note    如果被卡常了, 可以尝试加 inline
*/

#include <bits/stdc++.h>

constexpr double EPS = 1e-8; // 精度
// constexpr double PI = acos(-1); // not support on c++23
// constexpr double PI = 3.14159'26535'89793'23846'26433'83279'50288L;
constexpr double PI = std::numbers::pi;
struct Point { double x, y; };          // 点
using Vec = Point;
struct Line { Point P; Vec v; };        // 直线 (点向式)
struct Seg { Point A, B; };             // 线段
struct Circle { Point O; double r; };   // 圆

const Point O = {0,0};

// 基本  ============================================================

// 浮点数比较（考虑到精度）
// constexpr inline + 
bool eq(double a, double b) { return std::fabs(a-b)<EPS; }  // ==   //  ==
bool gt(double a, double b) { return a-b>EPS; }             // >    //  >
bool lt(double a, double b) { return a-b<-EPS; }            // <    //  <
bool ge(double a, double b) { return a-b>-EPS; }            // >=   //  >=
bool le(double a, double b) { return a-b<EPS; }             // <=   //  <=

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
Vec norm(Vec v) { auto L = len(v); return {v.x/L, v.y/L}; }         //  向量归一化
Vec pnorm(Vec v) { return (v.x<0?-1:1)/len(v)*v; }                  //  指向x轴正半轴的归一化向量


double theta(Point A) { return atan2(A.y, A.x); }                   //  求点的极角
void pointSort(std::vector<Point>&aa, Point C={0,0}) {              //  极角排序
    std::sort(aa.begin(), aa.end(), [&](const Point&A,const Point&B) {
        return lt(theta(A-C), theta(B-C));
    });
}

int qua(Point A) { return lt(A.y,0)<<1 | lt(A.x,0)^lt(A.y,0); }     //  求一个点的象限
void pointSort_byQua(std::vector<Point> &aa, Point C={0,0}) {       //  极角排序（根据叉乘）
    std::sort(aa.begin(), aa.end(),
        [&](const Point&A, const Point&B) {
            return qua(A-C) < qua(B-C)
            || qua(A-C) == qua(B-C) && gt((A-C)^(B-C), 0); // 逆时针排序
        }
    );
}

// 直线  ============================================================

Line line(double k, double b) { return {{0,b}, {1,k}}; }            //  直线（斜截式）
Line line(Point A, Point B) { return {A, B-A}; }                    //  直线（两点式）

Point pedal(Point P, Line l) { return l.P-(l.P-P)*l.v/(l.v*l.v)*l.v; }  // 求点到直线的垂足
Line perp(Point P, Line l) { return {P, r90c(l.v)}; }                //  过某点作直线的垂线
Line bisec(Point P, Vec u, Vec v) { return {P, norm(u)+norm(v)}; }   //  求角平分线

// 线段  ============================================================

Vec dVec(Seg l) { return l.B - l.A; } // 求线段方向向量              //  求线段方向向量
Point midP(Seg l) { return {(l.A.x+l.B.x)/2, (l.A.y+l.B.y)/2}; }    //  求线段中点
Line perp(Seg l) { return {midP(l), r90c(l.B-l.A)}; }               //  求线段中垂线

// 几何对象关系  ============================================================

double dis(Point A, Point B) { return hypot(A.x-B.x, A.y-B.y); }    //  两点之间距离
double dis(Point P, Line L) { return std::fabs(((P-L.P)^L.v)/len(L.v)); } // 点到直线距离
double dis(Line a, Line b) { return std::fabs((a.P^pnorm(a.v))-(b.P^pnorm(b.v))); } // 两平行直线间的距离

bool paral(Vec u, Vec v) { return eq(u^v, 0); }                     //  判断两向量是否平行
bool verti(Vec u, Vec v) { return eq(u*v, 0); }                     //  判断两向量是否垂直

bool p2lineR(Point P, Line l) { return ge((P-l.P)^l.v, 0); }        //  判断点是否在向量的右侧

bool on(Point P, Line l) { return eq((P.x-l.P.x)*l.v.y, (P.y-l.P.y)*l.v.x); } // 判断点是否在直线上
bool on(Point P, Seg l) { return eq(len(P-l.A)+len(P-l.B), len(l.A-l.B)); }   // 判断点是否在线段上
bool on(Point P, Circle C) { return eq(dis(P,C.O), C.r); }          // 判断点是否在圆上

bool operator==(Point A, Point B){ return eq(A.x,B.x)&&eq(A.y,B.y); } // 判断两点是否重合

bool tangency(Line l, Circle C){ return eq(fabs((C.O^l.v)-(l.P^l.v)), C.r*len(l.v)); } // 判断圆与直线是否相切
bool tangency(Circle C1, Circle C2){ return eq(len(C1.O-C2.O),C1.r+C2.r); } // 判断圆与圆是否相切

// 三角形  ============================================================

double triArea(Point A, Point B, Point C){ return std::fabs((B-A)^(C-A))/2; } // 三角形面积 triangle area
// double triArea(Point A, Point B, Point C){ return ((B-A)^(C-A))/2; } //  三角形面积（逆时针，有奇效）

Point centroid(Point A, Point B, Point C) {     // 三角形重心       //  三角形重心
    return {(A.x+B.x+C.x)/3, (A.y+B.y+C.y)/3};
}
Point circumcenter(Point A, Point B, Point C) { // 三角形外心       //  三角形外心
    double a = A*A, b = B*B, c = C*C;
    double d = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
    return 1 / d * r90c(a * (B - C) + b * (C - A) + c * (A - B));
}
Point incenter(Point A, Point B, Point C) {     // 三角形内心       //  三角形内心
    double a = len(B-C), b = len(C-A), c = len(A-B);
    double d = a + b + c;
    return 1 / d * (a * A + b * B + c * C);
}
Point orthocenter(Point A, Point B, Point C) {  // 三角形垂心       //  三角形垂心
    double n = B * (A - C), m = A * (B - C);
    double d = (B - C) ^ (A - C);
    return 1 / d * r90c(n * (C - B) - m * (C - A));
}

// 多边形  ============================================================

double polyArea(const std::vector<Point> &ps) { // 多边形面积       //  多边形面积
    double ans = ps.back() ^ ps.front();
    for(int i=1; i<ps.size(); ++i) ans += ps[i-1] ^ ps[i];
    return ans / 2;
}

Point polyCentroid(const std::vector<Point>&ps) { // 多边形重心     // 多边形重心
    double area = polyArea(ps);
    assert(!eq(area,0));
    Point ans = (ps.back()^ps.front())*(ps.back()+ps.front());
    for(int i=1, n=ps.size();i<n;++i) ans = ans+(ps[i-1]^ps[i])*(ps[i-1]+ps[i]);
    return 1/(6*area)*ans;
}

// 要求多边形是一个凸包，点逆时针排布
int inConvexPoly(Point P, std::vector<Point>&ps) { // 点是否在凸多边形内, -1->外  0->边界  1->内
    int n = ps.size();
    for(int i=0;i<n;++i) {
        if(gt((P-ps[i])^(P-ps[(i+1)%n]), 0)) return -1;
        if(on(P,Seg(ps[i],ps[(i+1)%n]))) return 0;
    }
    return 1;
}

//  平移与旋转  ============================================================

Line operator+(Line l, Vec v) { return {l.P+v, l.v}; }
Seg operator+(Seg l, Vec v) { return {l.A+v, l.B+v}; }

Point rotate(Point P, double rad){                                  //  P点绕原点逆时针旋转
    return {cos(rad)*P.x-sin(rad)*P.y, sin(rad)*P.x+cos(rad)*P.y};
}
Point rotate(Point P, double rad, Point Q) { return Q+rotate(P-Q,rad); } // P点绕 Q点逆时针旋转
Line rotate(Line l, double rad, Point C=O) { return {rotate(l.P,rad,C), rotate(l.v,rad)}; }
Seg rotate(Seg l, double rad, Point C=O) { return {rotate(l.A,rad,C), rotate(l.A,rad,C)}; }

//  对称  ============================================================

Point reflect(Point A, Point P){ return {P.x*2-A.x, P.y*2-A.y}; }   //  点关于点对称
Line reflect(Line l, Point P){ return {reflect(l.P,P), l.v}; }      //  直线关于点对称
Seg reflect(Seg l, Point P){ return {reflect(l.A,P), reflect(l.B,P)}; } // 线段关于点对称

Point reflect(Point A, Line l){ return reflect(A,pedal(A,l)); }     //  点关于直线对称
Vec reflect_v(Vec v, Line l){ return reflect(v,l)-reflect(O,l); }   //  向量关于直线对称
Line reflect(Line l1, Line l){ return {reflect(l1.P,l), reflect_v(l1.v,l)}; } // 直线关于直线对称
Seg reflect(Seg l1, Line l){ return {reflect(l1.A,l), reflect(l1.B,l)}; } // 线段关于直线对称

//  交点  ============================================================

Point inter(Line a, Line b) { // 求两直线交点                        //  求两直线交点
    double c = a.v ^ b.v;
    if(eq(c, 0)) return {};
    Vec v = 1/c * Vec(a.P ^ (a.P + a.v), b.P ^ (b.P + b.v));
    return Point(v * Vec(-b.v.x, a.v.x), v * Vec(-b.v.y, a.v.y));
}

std::vector<Point> inter(Line l, Circle C) { // 直线与圆交点        //  直线与圆交点
    Point P = pedal(C.O, l);
    double h = dis(P, C.O);
    if (gt(h, C.r)) return {};
    if (eq(h, C.r)) return {P};
    double d = sqrt(C.r * C.r - h * h);
    Vec vec = d / len(l.v) * l.v;
    return {P + vec, P - vec};
}

std::vector<Point> inter(Circle C1, Circle C2) { // 圆与圆交点      //  圆与圆交点
    Vec v1 = C2.O-C1.O, v2 = r90c(v1);
    double d = dis(C1.O, C2.O);
    if(gt(d,C1.r+C2.r) || gt(std::fabs(C1.r-C2.r),d)) return {};
    if(eq(d,C1.r+C2.r) || eq(std::fabs(C1.r-C2.r),d)) return {C1.O+C1.r/d*v1};
    double a = ((C1.r*C1.r-C2.r*C2.r)/d+d)/2;
    double h = sqrt(C1.r*C1.r-a*a);
    Vec av = a/len(v1)*v1, hv = h/len(v2)*v2;
    return {C1.O+av+hv, C1.O+av-hv};
}