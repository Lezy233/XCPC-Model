// 真的是模板题吗，我保持怀疑
#include <bits/stdc++.h>
typedef unsigned int uint;

uint seed;
inline uint getnext() {
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<5;
    return seed;
}

int main()
{
    uint n; std::cin>>n>>seed;
    std::vector<uint>f(n+1);
    for(int i=1;i<=n;++i) f[i]=getnext();

    uint res=0;
    std::vector<bool>isPrime(n+1,true);
    isPrime[1]=false;
    for(int i=1;i<=n;++i){
        if(isPrime[i]) for(int id=1, j=i;j<=n;j+=i){
            isPrime[j]=false;
            f[j]+=f[id++];
        }
        res^=f[i];
    }
    std::cout<<res<<"\n";
    return 0;
}