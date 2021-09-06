#pragma once
#include <iostream>

template<typename T>
class Point_impl {
public:
    T x;
    T y;

    using value_type = T;
    template <typename U>
    friend class Point_impl;

    Point_impl() : x{}, y{} {}            // default
    Point_impl(T x, T y) : x{ x }, y{ y } {}  // conversion
    Point_impl(const Point_impl& p) { x = p.x; y = p.y; } //copy
    
    // create one Point_impl<T> from a Point_impl<U> 
    template<typename U>
    Point_impl(const Point_impl<U>& rhs) :
        x{ static_cast<T>(rhs.x) },
        y{ static_cast<T>(rhs.y) }
    {}

    // add a Point_impl<U> to *this
    template<typename U>
    Point_impl<T>& operator+=(const Point_impl<U>& rhs) {
        x += static_cast<U>(rhs.x);
        y += static_cast<U>(rhs.y);
        return *this;
    }

    template<typename U>
    Point_impl<T>& operator-=(const Point_impl<U>& rhs) {
        x -= static_cast<U>(rhs.x);
        y -= static_cast<U>(rhs.y);
        return *this;
    }

    template<typename U>
    Point_impl<T>& operator*=(const Point_impl<U>& rhs) {
        x *= static_cast<U>(rhs.x);
        y *= static_cast<U>(rhs.y);
        return *this;
    }

    template<typename U>
    Point_impl<T>& operator/=(const Point_impl<U>& rhs) {
        x /= static_cast<U>(rhs.x);
        y /= static_cast<U>(rhs.y);
        return *this;
    }

    // for printing a point:
    friend std::ostream& operator<<(std::ostream& os, const Point_impl<T>& p) {
        return os << '(' << p.x << ',' << p.y << ')';
    }


    template<typename R>
    // for conversion:
    explicit operator Point_impl<R>() {
        return Point_impl<R>(static_cast<R>(x), static_cast<R>(y));
    }

};

template<typename L, typename R>
auto operator+(const Point_impl<L>& lhs, const Point_impl<R>& rhs) {
    // return the properly promoted Point_impl type deduced from if the
    // underlying types where added
    Point_impl<decltype(lhs.x + rhs.x)> rv = lhs;
    rv += rhs;
    return rv;
}

template<typename L, typename R>
auto operator-(const Point_impl<L>& lhs, const Point_impl<R>& rhs) {
    Point_impl<decltype(lhs.x - rhs.x)> rv = lhs;
    rv -= rhs;
    return rv;
}

template<typename L, typename R>
auto operator*(const Point_impl<L>& lhs, const Point_impl<R>& rhs) {
    Point_impl<decltype(lhs.x* rhs.x)> rv = lhs;
    rv *= rhs;
    return rv;
}

template<typename L, typename R>
auto operator/(const Point_impl<L>& lhs, const Point_impl<R>& rhs) {
    Point_impl<decltype(lhs.x / rhs.x)> rv = lhs;
    rv /= rhs;
    return rv;
}



//add something that isnt a point
template<typename L, typename R>
auto operator+(const Point_impl<L>& lhs, R rhs) {
    Point_impl<decltype(lhs.x + rhs)> rv = lhs;
    rv.x += rhs;
    rv.y += rhs;
    return rv;
}

template<typename L, typename R>
auto operator-(const Point_impl<L>& lhs, R rhs) {
    Point_impl<decltype(lhs.x + rhs)> rv = lhs;
    rv.x -= rhs;
    rv.y -= rhs;
    return rv;
}

template<typename L, typename R>
auto operator*(const Point_impl<L>& lhs, R rhs) {
    Point_impl<decltype(lhs.x + rhs)> rv = lhs;
    rv.x *= rhs;
    rv.y *= rhs;
    return rv;
}

template<typename L, typename R>
auto operator/(const Point_impl<L>& lhs, R rhs) {
    Point_impl<decltype(lhs.x + rhs)> rv = lhs;
    rv.x /= rhs;
    rv.y /= rhs;
    return rv;
}

template<typename L, typename R>
auto operator%(const Point_impl<L>& lhs, R rhs) {
    Point_impl<decltype(lhs.x + rhs)> rv = lhs;
    rv.x %= rhs;
    rv.y %= rhs;
    return rv;
}

//comapre
template<typename L, typename R>
auto operator==(const Point_impl<L>& lhs, const Point_impl<R>& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

template<typename L, typename R>
auto operator<(const Point_impl<L>& lhs, const Point_impl<R>& rhs) {
    return lhs.x < rhs.x || (rhs.x == lhs.x && rhs.y < lhs.y);
}

//math functions
template<typename L>
Point_impl<L> floor(const Point_impl<L>& lhs) {
    return Point_impl<L>(floor(lhs.x), floor(lhs.y));
}

template<typename L>
Point_impl<L> round(const Point_impl<L>& lhs) {
    return Point_impl<L>(round(lhs.x), round(lhs.y));
}

template<typename L>
Point_impl<L> abs(const Point_impl<L>& lhs) {
    return Point_impl<L>(abs(lhs.x), abs(lhs.y));
}

//vector functions
template<typename L>
int magnitude(const Point_impl<L>& lhs) {
    return sqrt( lhs.x*lhs.x + lhs.y * lhs.y );
}

template<typename L>
int sqrMagnitude(const Point_impl<L>& lhs) { //cheaper then magnitude
    return lhs.x * lhs.x + lhs.y * lhs.y;
}

using PointI = Point_impl<int>;
using PointF = Point_impl<float>;