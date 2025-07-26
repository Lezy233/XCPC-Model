/**
 * @brief   Minkowski Sum   闵可夫斯基和
 * @warning 需要根据题意变化, 例如本题(Luogu P4557)中待求的是凸包B平移后是否与凸包A有交点, 即 B+vec=A
 *          此时转化为 vec \in A-B, 由此求的是 A与-B的闵可夫斯基和
*/

#include <bits/stdc++.h>
using std::cin,std::cout,std::vector;
#define endl "\n"
typedef std::pair<int,int> PII;

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

double dis(Point A, Point B){ return hypot(A.x-B.x,A.y-B.y); }      //  两点之间距离

void convex_hull(std::vector<Point>&aa, std::vector<Point>&ch) {
    std::sort(aa.begin(),aa.end(),[](const Point&A,const Point&B){
        if(A.x!=B.x) return A.x<B.x;
        return A.y<B.y;
    });
    for(auto &v:aa){
        while(ch.size()>=2 && le((ch.back()-ch[ch.size()-2])^(v-ch.back()),0)) ch.pop_back();
        ch.emplace_back(v);
    }
    for(int last_siz=ch.size(), i=aa.size()-2; i>=0; --i){
        while(ch.size()>last_siz && le((ch.back()-ch[ch.size()-2])^(aa[i]-ch.back()),0)) ch.pop_back();
        ch.emplace_back(aa[i]);
    }
    if(ch.size()>1) ch.pop_back(); // 最左边一点重复计算
}

// 求闵可夫斯基和
void Minkowski(std::vector<Point>&psN, std::vector<Point>&psM, std::vector<Point>&M) { 
    int n=psN.size(), m=psM.size();
    std::vector<Vec>vecN(n), vecM(m);
    for(int i=0;i<n;++i) vecN[i]=psN[(i+1)%n]-psN[i];
    for(int i=0;i<m;++i) vecM[i]=psM[(i+1)%m]-psM[i];

    M.resize(1,psN[0]+psM[0]);
    int i=0, j=0;
    while(i<n&&j<m)
        M.emplace_back(M.back()+((vecN[i]^vecM[j])>0? vecN[i++]:vecM[j++]));
    while(i<n) M.emplace_back(M.back()+vecN[i++]);
    while(j<m) M.emplace_back(M.back()+vecM[j++]);

    std::vector<Point>tmp;
    convex_hull(M,tmp);
    std::swap(M,tmp);
}

// 判断点是否在凸包内（包括边界）
bool inConvex(Point A, std::vector<Point>&ps) {
    int L=1, R=ps.size()-1;
    while(L<=R){
        int mid=L+R>>1;
        double a1=(ps[mid-1]-ps[0])^(A-ps[0]);
        double a2=(ps[mid]-ps[0])^(A-ps[0]);
        if(ge(a1,0)&&le(a2,0)){
            auto tt=(ps[mid]-ps[mid-1])^(A-ps[mid-1]);
            if(eq(tt,0)) return ge(dis(ps[mid],ps[mid-1]),dis(A,ps[mid-1]));
            return gt(tt,0);
        }
        if(lt(a1,0)) R=mid-1;
        else L=mid+1;
    }
    return false;
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q; std::cin>>n>>m>>q;
    std::vector<Point>psN(n), psM(m);
    for(auto &[x,y]:psN){
        int xx,yy; std::cin>>xx>>yy;
        x=xx, y=yy;
    }
    for(auto &[x,y]:psM){
        int xx,yy; std::cin>>xx>>yy;
        x=-xx, y=-yy;
    }
    std::vector<Point>chN, chM;
    convex_hull(psN,chN);
    convex_hull(psM,chM);
    std::vector<Point>M;
    Minkowski(chN,chM,M);

    while(q--){
        int dx,dy; std::cin>>dx>>dy;
        cout<<inConvex(Point(dx,dy),M)<<endl;
    }
    return 0;
}