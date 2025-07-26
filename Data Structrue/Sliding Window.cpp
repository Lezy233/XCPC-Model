#include <bits/stdc++.h>

// 采用两个multiset维护滑动窗口中的前k小值
template <typename T>
class SlidingWindow
{
private:
    std::multiset<T>st1,st2;

    void adjust() {
        while(st1.size()<K&&st2.size()){
            T t=*(st2.begin());
            st1.emplace(t);
            sum+=t;
            st2.erase(st2.begin());
        }
        while(st1.size()>K){
            T t=*(st1.rbegin());
            st2.emplace(t);
            st1.erase(std::prev(st1.end()));
            sum-=t;
        }
    }
public:
    int K;
    T sum;
    SlidingWindow(int _k): K(_k), sum(0) {}

    void add(T x) {
        if(st2.size()&&x>=*(st2.begin())) st2.emplace(x);
        else st1.emplace(x), sum+=x;
        adjust();
    }

    void del(T x) {
        auto it=st1.find(x);
        if(it==st1.end()) st2.erase(st2.find(x));
        else st1.erase(it), sum-=x;
        adjust();
    }
};