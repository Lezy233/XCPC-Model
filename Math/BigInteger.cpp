/**
 * @brief   BigInteger 高精度
 */
// P1932
#include <bits/stdc++.h>
using std::cin,std::cout,std::vector,std::array;
#define endl "\n"
typedef long long ll;
typedef std::pair<int,int> PII;
typedef std::tuple<int,int,int> T3I;

struct BigInteger {
    std::vector<int>d;
  
    constexpr BigInteger(long long num=0){ *this=num; }
    constexpr BigInteger(const std::string &num){ *this=num; }

    constexpr BigInteger operator = (long long num) {
        for(d.clear(); num; num/=10) d.emplace_back(num%10);
        if(d.empty()) d.emplace_back(0);
        return *this;
    }

    constexpr BigInteger operator = (const std::string &num) {
        for(d.clear(); auto i:std::views::reverse(num)) d.emplace_back(i-'0');
        return *this;
    }

    constexpr BigInteger norm() {
        while(d.size()>1 && !d.back()) d.pop_back();
        for(int i=0; i<d.size()-1; ++i){
            if(d[i]>=0 && d[i]<10) continue;
            d[i+1]+=d[i]/10;
            if((d[i]%=10) < 0) d[i]+=10, --d[i+1];
        }
        while(d.back()>9){
            d.emplace_back(d.back()/10);
            d[d.size()-2]%=10;
        }
        while(d.size()>1 && !d.back()) d.pop_back();
        return *this;
    }

    constexpr BigInteger &operator += (const BigInteger &rhs) {
        if(d.size()<rhs.d.size()) d.resize(rhs.d.size());
        for(int i=0 ; i<rhs.d.size(); ++i) d[i]+=rhs.d[i];
        norm();
        return *this;
    }

    constexpr BigInteger add (const int rhs) { // + int
        d[0]+=rhs;
        for(int i=0; i<d.size()-1; ++i){
            if(d[i]>=0 && d[i]<10) break;
            d[i+1]+=d[i]/10;
            if((d[i]%=10) < 0) d[i]+=10, --d[i+1];
        }
        if(d.back()>9) d.back()-=10, d.emplace_back(1);
        while(d.size()>1 && !d.back()) d.pop_back();
        return *this;
    }

    constexpr BigInteger &operator -= (const BigInteger &rhs) {
        if(d.size()<rhs.d.size()) d.resize(rhs.d.size());
        for(int i=0; i<rhs.d.size(); ++i) d[i]-= rhs.d[i];
        norm();
        return *this;
    }

    constexpr BigInteger mul (const int rhs) { // * int
        if(rhs==10){ d.insert(d.begin(),0); return *this; }
        for(auto &i:d) i*=rhs;
        norm();
        return *this;
    }

    constexpr BigInteger &operator *= (const BigInteger &rhs) {
        BigInteger ans;
        ans.d.resize(d.size()+rhs.d.size());
        for(int i=0; i<d.size(); ++i) for(int j=0;j<rhs.d.size();++j)
            ans.d[i+j] += d[i]*rhs.d[j];
        std::swap(d,ans.d);
        norm();
        return *this;
    }

    constexpr BigInteger div (const int rhs) { // / int
        BigInteger ans=0;
        ans.d.resize(d.size(),0);
        long long last=0;
        for(int i=d.size()-1; ~i; --i){
            (last*=10)+=d[i];
            ans.d[i]=last/rhs;
            last%=rhs;
        }
        std::swap(d,ans.d);
        while(d.size()>1 && !d.back()) d.pop_back();
        return *this;
    }

    constexpr int mod (const int rhs) {
        long long ans=0;
        for(auto &i:std::views::reverse(d)) ((ans*=10)+=i)%=rhs;
        return ans;
    }

    constexpr BigInteger &operator %= (const BigInteger &rhs) {
        BigInteger last=0;
        std::array<BigInteger,11>tt={};
        for(int i=1;i<=10;++i) tt[i]=tt[i-1], tt[i]+=rhs;
        for(int i:std::views::reverse(d)){
            (last*=10).add(i);
            int j=0;
            for(; j<10; ++j) if(last<tt[j+1]) break;
            if(j) last-=tt[j];
        }
        std::swap(d,last.d);
        return *this;
    }

    friend constexpr BigInteger add (BigInteger lhs, const int &rhs){ return lhs.add(rhs); }
    friend constexpr BigInteger mul (BigInteger lhs, const int &rhs){ return lhs.mul(rhs); }
    friend constexpr BigInteger div (BigInteger lhs, const int &rhs){ return lhs.div(rhs); }
    friend constexpr BigInteger mod (BigInteger lhs, const int &rhs){ return lhs.mod(rhs); }
    friend constexpr BigInteger operator + (BigInteger lhs, const BigInteger &rhs){ return lhs+=rhs; }
    friend constexpr BigInteger operator - (BigInteger lhs, const BigInteger &rhs){ return lhs-=rhs; }
    friend constexpr BigInteger operator * (BigInteger lhs, const BigInteger &rhs){ return lhs*=rhs; }
    friend constexpr BigInteger operator / (const BigInteger &lhs, const BigInteger &rhs) {
        BigInteger ans, last=0;
        ans.d.resize(lhs.d.size(),0);
        std::array<BigInteger,11>tt={};
        for(int i=1;i<=10;++i) tt[i]=tt[i-1], tt[i]+=rhs;
        for(int i=lhs.d.size()-1; i>=0; --i){
            (last*=10).add(lhs.d[i]);
            int j=0;
            for(; j<10; ++j) if(last<tt[j+1]) break;
            ans.d[i]=j;
            if(j) last-=tt[j];
        }
        while(ans.d.size()>1 && !ans.d.back()) ans.d.pop_back();
        return ans;
    }
    friend constexpr BigInteger operator % (BigInteger lhs, const BigInteger &rhs){ return lhs%=rhs; }
        
    constexpr bool operator <(const BigInteger &rhs) const{
        if(d.size() != rhs.d.size()) return d.size() < rhs.d.size();
        for(int i=d.size()-1; ~i; --i)
            if(d[i] != rhs.d[i]) return d[i] < rhs.d[i];
        return false;
    }  
    bool operator >(const BigInteger& b) const { return b<*this; }
    bool operator<=(const BigInteger& b) const { return !(b<*this); }
    bool operator>=(const BigInteger& b) const { return !(*this<b); }
    bool operator!=(const BigInteger& b) const { return d!=b.d; }
    bool operator==(const BigInteger& b) const { return d==b.d; }
  
    std::string str() const {
        std::string ans;
        for(int i:std::views::reverse(d)) ans += '0'+i;
        return ans;
    }

    friend std::istream &operator>>(std::istream &is, BigInteger &x){
        std::string S; std::cin>>S;
        x = S;
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const BigInteger &x){ return os<<x.str(); }
};

int main()
{
    std::cin.tie(nullptr)->sync_with_stdio(false);
    BigInteger lhs,rhs; cin>>lhs>>rhs;
    cout<<lhs+rhs<<endl;
    if(lhs<rhs) cout<<'-'<<rhs-lhs<<endl;
    else cout<<lhs-rhs<<endl;
    cout<<lhs*rhs<<endl;
    cout<<lhs/rhs<<endl;
    cout<<lhs%rhs<<endl;
    return 0;
}