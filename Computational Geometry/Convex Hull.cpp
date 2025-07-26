// Convex Hull 凸包

// P2742
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"

constexpr double EPS = 1e-6; // 精度
constexpr double PI = std::numbers::pi;
struct Point { double x, y; };
using Vec = Point;
struct Line { Point P; Vec v; };        // 直线（点向式）
struct Seg { Point A,B; };              // 线段
struct Circle { Point O; double r; };   // 圆

// 浮点数比较（考虑到精度）
bool eq(double a, double b) { return std::abs(a-b) < EPS; } // ==
bool gt(double a, double b) { return a-b > EPS; }           // >
bool lt(double a, double b) { return a-b < -EPS; }          // <
bool ge(double a, double b) { return a-b > -EPS; }          // >=
bool le(double a, double b) { return a-b < EPS; }           // <=

Vec r90a(Vec v) { return {-v.y, v.x}; }                             // 逆时针旋转90度的向量
Vec r90c(Vec v) { return {v.y, -v.x}; }                             // 顺时针旋转90度的向量
Vec operator+(Vec u, Vec v) { return {u.x + v.x, u.y + v.y}; }      // 向量加向量
Vec operator-(Vec u, Vec v) { return {u.x - v.x, u.y - v.y}; }      // 向量减向量（两个点得向量）
Vec operator*(double k, Vec v) { return {k * v.x, k * v.y}; }       // 数乘
Vec operator*(Vec v, double k) { return {k * v.x, k * v.y}; }       // 数乘（两个方向）
double operator*(Vec u, Vec v) { return u.x * v.x + u.y * v.y; }    // 点乘
double operator^(Vec u, Vec v) { return u.x * v.y - u.y * v.x; }    // 叉乘
double len(Vec v) { return sqrt(v.x * v.x + v.y * v.y); }           // 向量长度
double toArc(double x) { return PI*x/180.0; }                       // 角度转弧度

double dis(Point A, Point B) { return hypot(A.x-B.x, A.y-B.y); }    //  两点之间距离

void convex_hull(std::vector<Point>&ps, std::vector<Point>&ch) {
    std::ranges::sort(ps,[](const Point&A,const Point&B){
        return A.x<B.x || A.x==B.x&&A.y<B.y;
    });
    for(auto &v:ps) {
        while(ch.size()>=2 && le((ch.back()-ch[ch.size()-2])^(v-ch.back()),0)) ch.pop_back();
        ch.emplace_back(v);
    }
    for(int last_siz=ch.size(), i=ps.size()-2; i>=0; --i) {
        while(ch.size()>last_siz && le((ch.back()-ch[ch.size()-2])^(ps[i]-ch.back()),0)) ch.pop_back();
        ch.emplace_back(ps[i]);
    }
    if(ch.size() > 1) ch.pop_back(); // 最左边一点重复计算
}

// 判断点是否在凸包内（包括边界）
bool inConvex(Point A, std::vector<Point>&ps) {
    int L=1, R=ps.size()-1;
    while(L <= R) {
        auto mid = std::midpoint(L, R);
        double a1 = (ps[mid-1]-ps[0])^(A-ps[0]);
        double a2 = (ps[mid]-ps[0])^(A-ps[0]);
        if(ge(a1, 0) && le(a2, 0)) {
            auto tt = (ps[mid]-ps[mid-1])^(A-ps[mid-1]);
            if(eq(tt, 0)) return ge(dis(ps[mid],ps[mid-1]), dis(A,ps[mid-1]));
            return gt(tt, 0);
        }
        if(lt(a1, 0)) R = mid-1;
        else L = mid+1;
    }
    return false;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin >> n;
    vector<Point> aa(n), ch;
    for(auto &[x,y]:aa) cin >> x >> y;
    convex_hull(aa, ch);
    double res = dis(ch.front(), ch.back());
    for(int i=1; i<ch.size(); ++i) res += dis(ch[i], ch[i-1]);
    std::cout << std::fixed << std::setprecision(2) << res << endl;
    return 0;
}