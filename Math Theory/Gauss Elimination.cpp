// P2455
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;

constexpr double EPS = 1e-9;

constexpr bool eq(const double &lhs, const double &rhs){ return std::abs(lhs-rhs)<EPS; }

std::vector<double>& operator+=(std::vector<double> &lhs, const std::vector<double> &rhs) {
    assert(lhs.size()==rhs.size());
    for(int i=0; i<lhs.size(); ++i) lhs[i] += rhs[i];
    return lhs;
}
std::vector<double> operator*(const std::vector<double> &lhs, const double &rhs) {
    std::vector<double> ans(lhs.size());
    for(int i=0; i<lhs.size(); ++i)
        ans[i] = lhs[i]*rhs;
    return ans;
}
std::vector<double>& operator*=(std::vector<double> &lhs, const double &rhs) {
    for(auto &i:lhs) i *= rhs;
    return lhs;
}
std::vector<double>& operator/=(std::vector<double> &lhs, const double &rhs) {
    return lhs *= 1/rhs;
}

void solve()
{
    int n; cin>>n;
    vector<vector<double>> Mart(n, vector<double>(n+1));
    for(auto &i:Mart) for(auto &j:i){
        int t; cin>>t;
        j = t;
    }
    int nxt = 0;
    for(int j=0; j<n; ++j){ // 第j列
        int t = nxt;
        while(t<n && eq(Mart[t][j], 0)) ++t;
        if(t==n) continue;
        std::swap(Mart[nxt], Mart[t]);
        Mart[nxt] /= Mart[nxt][j];
        for(int i=0; i<n; ++i){
            if(i==nxt || eq(Mart[i][j], 0)) continue;
            Mart[i] += Mart[nxt]*(-Mart[i][j]);
        }
        ++nxt;
    }
    bool inf = false;
    for(int i=0; i<n; ++i){
        bool fl = false;
        for(int j=0; j<n; ++j) if(!eq(Mart[i][j], 0)){ fl = true; break; }
        if(fl) continue;
        if(eq(Mart[i][n], 0)) inf = true;
        else{ cout<<-1<<"\n"; return; }
    }
    if(inf) cout<<0<<"\n";
    else{
        for(int i=0; i<n; ++i)
            cout<<"x"<<i+1<<"="<<std::fixed<<std::setprecision(4)<<Mart[i][n]<<"\n";
    }
}

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    std::ifstream in("C++/in.txt");
    std::cin.rdbuf(in.rdbuf());
#endif
    int T = 1;
    // std::cin>>T;
    while(T--) solve();
    return 0;
}