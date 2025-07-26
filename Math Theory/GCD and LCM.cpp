/*
写在前面
最大公约数(GCD)Greatest Common Divisor
最小公倍数(LCM)Least Common Multiple
*/
#include<bits/stdc++.h>
using namespace std;
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b){
    return a/gcd(a,b)*b;
}
int main()
{

}