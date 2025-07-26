/**
 * @brief   Nim Game 尼姆游戏
 */
// HDU-1848
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;

constexpr int N = 1000;
vector<int> fab{1, 2};
array<int,N+1> SG{};
array<array<bool,N+1>,N+1> nxt{};
auto init = []{
    while(fab.back()<N) fab.emplace_back(fab[fab.size()-2]+fab.back());
    for(int u=0;u<=N;++u){
        SG[u] = 0;
        while(SG[u]<N && nxt[u][SG[u]]) ++SG[u];
        for(auto &d:fab){
            int v = u+d;
            if(v>N) break;
            nxt[v][SG[u]] = true;
        }
    }
    return 0;
}();

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    std::ifstream in("C++/in.txt");
    std::cin.rdbuf(in.rdbuf());
#endif
    array<int,3> aa;
    for(auto &i:aa) cin>>i;
    while(aa[0]){
        int sum = 0;
        for(auto &i:aa) sum ^= SG[i];
        if(sum) cout<<"Fibo\n";
        else cout<<"Nacci\n";
        for(auto &i:aa) cin>>i;
    }
    return 0;
}