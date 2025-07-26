/**
 * @note    如果在比赛中还是TLE了, 可能是使用cin输入浮点数太慢导致的
 *          可以使用一下快读
 */

#include <bits/stdc++.h>

template <typename T>
inline void read(T &x) {
    x=0; bool f=false; char c=getchar();
    while(c<'0'||c>'9'){ if(c=='-') f=true; c=getchar(); }
    while(c>='0'&&c<='9'){ x=(x*10)+(c^48); c=getchar(); }
    if(f) x=-x;
}
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, void>::type
read(T &x) {
    std::string s; std::cin>>s;
    x = std::stod(s);
}

template <typename T, typename ...Args>
inline void read(T &tmp,Args &...tmps){ read(tmp); read(tmps...); }