#include <bits/stdc++.h>

template <class T>
struct Frac {
    T num, den;
    Frac(T num_ = 0, T den_ = 1): num(num_), den(den_) {
        if(den < 0) { den = -den, num = -num; }
        norm();
    }
    explicit operator double() const { return 1. * num / den; }
    constexpr void norm() {
        auto GCD = std::gcd(num, den);
        num /= GCD, den /= GCD;
    }
    Frac &operator+=(const Frac &rhs) {
        num = num * rhs.den + rhs.num * den;
        den *= rhs.den;
        norm();
        return *this;
    }
    Frac &operator-=(const Frac &rhs) {
        num = num * rhs.den - rhs.num * den;
        den *= rhs.den;
        norm();
        return *this;
    }
    Frac &operator*=(const Frac &rhs) {
        num *= rhs.num, den *= rhs.den;
        norm();
        return *this;
    }
    Frac &operator/=(const Frac &rhs) {
        num *= rhs.den;
        den *= rhs.num;
        if(den < 0) { num = -num, den = -den; }
        return *this;
    }
    friend Frac operator+(Frac lhs, const Frac &rhs) { return lhs += rhs; }
    friend Frac operator-(Frac lhs, const Frac &rhs) { return lhs -= rhs; }
    friend Frac operator*(Frac lhs, const Frac &rhs) { return lhs *= rhs; }
    friend Frac operator/(Frac lhs, const Frac &rhs) { return lhs /= rhs; }
    friend Frac operator- (const Frac &a) { return Frac(-a.num, a.den); }
    friend bool operator==(const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den == rhs.num * lhs.den; }
    friend bool operator!=(const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den != rhs.num * lhs.den; }
    friend bool operator< (const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den < rhs.num * lhs.den; }
    friend bool operator> (const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den > rhs.num * lhs.den; }
    friend bool operator<=(const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den <= rhs.num * lhs.den; }
    friend bool operator>=(const Frac &lhs, const Frac &rhs) { return lhs.num * rhs.den >= rhs.num * lhs.den; }
};