// Rotating Calipers 旋转卡壳

// P1452 AC
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"

const double EPS=1e-6; // 精度
const double PI=acos(-1);
struct Point { double x, y; };
using Vec=Point;
struct Line { Point P; Vec v; };        // 直线（点向式）
struct Seg { Point A,B; };              // 线段
struct Circle { Point O; double r; };   // 圆

// 浮点数比较（考虑到精度）
bool eq(double a, double b){ return std::abs(a-b)<EPS; }    // ==
bool gt(double a, double b){ return a-b>EPS; }              // >
bool lt(double a, double b){ return a-b<-EPS; }             // <
bool ge(double a, double b){ return a-b>-EPS; }             // >=
bool le(double a, double b){ return a-b<EPS; }              // <=

Vec r90a(Vec v) { return {-v.y, v.x}; }                             // 逆时针旋转90度的向量
Vec r90c(Vec v) { return {v.y, -v.x}; }                             // 顺时针旋转90度的向量
Vec operator+(Vec u, Vec v) { return {u.x + v.x, u.y + v.y}; }      // 向量加向量
Vec operator-(Vec u, Vec v) { return {u.x - v.x, u.y - v.y}; }      // 向量减向量（两个点得向量）
Vec operator*(double k, Vec v) { return {k * v.x, k * v.y}; }       // 数乘
Vec operator*(Vec v, double k) { return {k * v.x, k * v.y}; }       // 数乘（两个方向）
double operator*(Vec u, Vec v) { return u.x * v.x + u.y * v.y; }    // 点乘
double operator^(Vec u, Vec v) { return u.x * v.y - u.y * v.x; }    // 叉乘
double len(Vec v) { return sqrt(v.x * v.x + v.y * v.y); }           // 向量长度
double toArc(double x){ return PI*x/180.0; }                        // 角度转弧度

double getDis(Point x,Point y) { return hypot(x.x-y.x,x.y-y.y); }

void convex_hull(vector<Point>&aa, vector<Point>&ch) {
    std::sort(aa.begin(),aa.end(),[](const Point&A,const Point&B){
        if(A.x!=B.x) return A.x<B.x;
        return A.y<B.y;
    });
    for(auto &v:aa){
        while(ch.size()>=2 && le((ch.back()-ch[ch.size()-2])^(v-ch.back()),0)) ch.pop_back();
        ch.emplace_back(v);
    }
    int last_siz=ch.size();
    for(int i=aa.size()-2; i>=0; --i){
        while(ch.size()>last_siz && le((ch.back()-ch[ch.size()-2])^(aa[i]-ch.back()),0)) ch.pop_back();
        ch.emplace_back(aa[i]);
    }
    if(ch.size()>1) ch.pop_back(); // 最左边一点重复计算
}

double triArea(Point A, Point B, Point C) {  return std::fabs((B-A)^(C-A))/2.0; } // 三角形面积 triangle area

int main()
{
    std::ios::sync_with_stdio(false); cin.tie(0);
    srand(time(0));
    int n; cin>>n;
    vector<Point>aa(n), con; // con记录凸包
    for(auto &[x,y]:aa) cin>>x>>y;
    convex_hull(aa,con);
    n=con.size();
    double res=0;
    for(int j=1, i=0; i<n-1; ++i){ // i,i+1表示边   核心也就是这个for循环
        while(triArea(con[i],con[i+1],con[j])<triArea(con[i],con[i+1],con[(j+1)%n])) j=(j+1)%n;
        res=std::max({res,(con[j]-con[i])*(con[j]-con[i]),(con[j]-con[i+1])*(con[j]-con[i+1])});
    }
    cout<<int(res)<<endl;
    return 0;
}