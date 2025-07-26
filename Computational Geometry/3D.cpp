/**
 * @brief   Computational Geometry of three-dimensional
 * @warning WA的时候考虑：1.直线斜率是否存在, 2.精度问题
*/

#include <bits/stdc++.h>

constexpr const double EPS = 1e-12;   // 精度
constexpr const double PI = std::numbers::pi;
struct Point { double x, y, z; };
using Vec = Point;
struct Line { Point P; Vec v; };        //  直线 (点向式)
struct Seg { Point A, B; };             //  线段
struct Circle { Point O; double r; };   //  圆
struct Plane { Point A, B, C; };        //  平面

// 基本  ============================================================

// 浮点数比较（考虑到精度）
constexpr inline bool eq(const double &lhs, const double &rhs){ return std::fabs(lhs-rhs) < EPS; }  //  ==
constexpr inline bool gt(const double &lhs, const double &rhs){ return lhs-rhs > EPS; }             //  >
constexpr inline bool lt(const double &lhs, const double &rhs){ return lhs-rhs < -EPS; }            //  <
constexpr inline bool ge(const double &lhs, const double &rhs){ return lhs-rhs > -EPS; }            //  >=
constexpr inline bool le(const double &lhs, const double &rhs){ return lhs-rhs < EPS; }             //  <=

constexpr inline Vec operator+(const Vec &u, const Vec &v){ return {u.x+v.x, u.y+v.y, u.z+v.z}; }   //  向量减
constexpr inline Vec operator-(const Vec &u, const Vec &v){ return {u.x-v.x, u.y-v.y, u.z-v.z}; }   //  向量减
constexpr inline Vec operator*(double k, const Vec &v){ return {k*v.x, k*v.y, k*v.z}; }             //  数乘
constexpr inline Vec operator*(const Vec &v, double k){ return {k*v.x, k*v.y, k*v.z}; }             //  数乘（两个方向）
constexpr inline double operator*(const Vec &u, const Vec &v){ return u.x*v.x+u.y*v.y+u.z*v.z; }    //  点乘
constexpr inline Vec operator^(const Vec &u, const Vec &v) {        //  叉乘                        //  叉乘
    return {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
} // 叉乘
constexpr inline double len(const Vec &u){ return sqrt(u*u); }      //  向量长度
constexpr inline double len2(const Vec &u){ return u*u; }           //  向量长度平方

double toArc(double x) { return PI*x/180.0; }                       //  角度转弧度
constexpr Vec norm(Vec v){ auto L = len(v); return {v.x/L, v.y/L, v.z/L}; }   //  向量归一化

constexpr Line line(const Point &A, const Point &B){ return {A, B-A}; }

// 多边形  ============================================================

constexpr double triArea(const Point &A, const Point &B, const Point &C){ return len((B-A)^(C-A))/2; } // 三角形面积

// 多面体  ============================================================

constexpr double tetrVolume6(const Point &A, const Point &B, const Point &C, const Point &D) { //  四面体的体积的6倍
    return ((B-A)^(C-A))*(D-A); // 其实就是 AB,AC,AD的混合积 
}

// 平面  ============================================================

Vec pVec(Plane alp){ return (alp.B-alp.A)^(alp.C-alp.B); }  //  求平面法向量

// 直线满足方程 Ax+By+Cz+D=0
std::array<double, 4> plane(const Vec &lhs, const Vec &rhs, const Point P={0,0,0}) {
    assert(!eq(len2(lhs^rhs), 0));
    double A = lhs.y * rhs.z - lhs.z * rhs.y;
    double B = lhs.z * rhs.x - lhs.x * rhs.z;
    double C = lhs.x * rhs.y - lhs.y * rhs.x;
    double D = -(A * P.x + B * P.y + C * P.z);
    return {A, B, C, D};
};

// 几何对象关系  ============================================================

template <typename T>
constexpr int sign(const T &x) noexcept {
    if(x > T{0}) return 1;
    if(x < T{0}) return -1;
                 return 0;
}

// constexpr double dis(const Point &A, const Point &B){ return hypot(A.x-B.x, A.y-B.y, A.z-B.z); } // 两点距离
// 不知道为什么上面的方法在 linux 上破产了 :(
double dis(const Point &A, const Point &B) {    // 两点距离
    auto f = [](auto x) { return x*x; };
    return sqrt(f(A.x-B.x) + f(A.y-B.y) + f(A.z-B.z));
}

// constexpr double dis(const Point &A, const Line &l){ return fabs((A-l.P)^norm(l.v)); } // 点到直线距离

constexpr bool paral(const Vec &u, const Vec &v){ return eq(len(u^v),0); }          //  判断两向量是否平行
constexpr bool verti(const Vec &u, const Vec &v){ return eq(u*v,0); }               //  判断两向量是否垂直

constexpr bool ponPlane(const Point &A, const Point &B, const Point &C, const Point &D) {         //  判断四点共线
    return eq(pVec({A,B,C})*(D-A),0);
}

constexpr bool paral(const Plane &alp, const Plane &beta) { return paral(pVec(alp),pVec(beta)); } // 判断两平面是否平行
constexpr bool verti(const Plane &alp, const Plane &beta) { return verti(pVec(alp),pVec(beta)); } // 判断两平面是否垂直

constexpr bool on(const Point &P, const Line &l) { return verti(P-l.P,l.v); }       //  判断点在直线上
constexpr bool on(const Point &P, const Seg &l) { return eq(len(P-l.A)+len(P-l.B),len(l.B-l.A)); } // 判断点在线段上

bool collinear(const std::vector<Point> &ps) { // 判断多点共线
    if(ps.size()<3) return true;
    const Vec L = ps[1]-ps[0];
    for(int i=2; i<ps.size(); ++i)
        if(!eq(len(L^(ps[i]-ps[0])), 0)) return false;
    return true;
}

bool coplanar(const std::vector<Point> &ps) { // 判断多点共面
    if(ps.size()<4) return true;
    auto [A,B,C,D] = plane(ps[1]-ps[0], ps[2]-ps[0], ps[0]);
    auto cal = [&](const Point &P){ return A*P.x+B*P.y+C*P.z+D; };
    for(int i=3; i<ps.size(); ++i)
        if(!eq(cal(ps[i]), 0)) return false;
    return true;
}

// 投影  ============================================================

Point projPoint(const Point &P, const Line &l) { // 点到直线的投影
    auto lvec = norm(l.v);
    return l.P+((P-l.P)*lvec)*lvec;
}

int main()
{
    std::cout << __cplusplus << std::endl;
    return 0;
}