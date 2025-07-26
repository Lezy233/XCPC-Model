#include<bits/stdc++.h>
using namespace std;

// 快读 ----------------------
template <typename T>
void read(T &x) {
    x=0; bool f=false; char c=getchar();
    while(c<'0'||c>'9'){ if(c=='-') f=true; c=getchar(); }
    while(c>='0'&&c<='9'){ x=(x*10)+(c^48); c=getchar(); }
    if(f) x=-x;
}
template <typename T, typename ...Args>
void read(T &tmp,Args &...tmps){ read(tmp); read(tmps...); }

// 快写 ----------------------
template <typename T>
void print(T x) {
    if(x<0) putchar('-'), x=-x;
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
template <typename T>
void print(std::vector<T> &vec) {
    for(const auto &i:vec) print(i), putchar(' ');
    putchar('\n');
}

// by jiangly ---------------
char buf[1<<20], *p1 = buf, *p2 = buf;
inline char get() {
    if(p1 == p2) {
        p1 = buf;
        p2 = buf + fread(buf, 1, sizeof(buf), stdin);
        if(p1 == p2) return EOF;
    }
    return *p1++;
}
int readInt() {
    int x = 0; char c = get();
    while(!std::isdigit(c)) c = get();
    while(std::isdigit(c)){ x = (x*10)+(c^48); c = get(); }
    return x;
}
void print(int x) {
    static char stk[20];
    int top = 0;
    while(x > 0) {
        stk[top++] = x%10 + '0';
        x /= 10;
    }
    for(int i=top-1; i>=0; --i) *p2++ = stk[i];
    *p2++ = '\n';
}

int main()
{
    __int128_t T; read(T);
    print(T);
    std::vector<int>aa={1,2,3,4,5};
    std::vector bb(7,aa);
    print(bb);
    return 0;
}