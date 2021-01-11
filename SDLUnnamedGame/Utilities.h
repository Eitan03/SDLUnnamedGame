#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
typedef SDL_Rect Rect;


struct Color {
	Color(unsigned char r, unsigned char b, unsigned char g, unsigned char a = 0xFF) : r(r), b(b), g(g), a(a) {}
	unsigned char r;
	unsigned char b;
	unsigned char g;
	unsigned char a = 0xFF;
	SDL_Color ToSDL() { return { r, g, b, a }; }
};

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

    template<typename T, typename R>
    // for conversion:
    auto operator R() {
        return Point_impl<R>(static_cast<R>x, static_cast<R>y);
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

//floats
template<typename L>
auto operator+(const Point_impl<L>& lhs, float rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x += rhs;
    rv.y += rhs;
    return rv;
}

template<typename L>
auto operator-(const Point_impl<L>& lhs, float rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x -= rhs;
    rv.y -= rhs;
    return rv;
}

template<typename L>
auto operator*(const Point_impl<L>& lhs, float rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x *= rhs;
    rv.y *= rhs;
    return rv;
}

template<typename L>
auto operator/(const Point_impl<L>& lhs, float rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x /= rhs;
    rv.y /= rhs;
    return rv;
}

//ints
template<typename L>
auto operator+(const Point_impl<L>& lhs, int rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x += rhs;
    rv.y += rhs;
    return rv;
}

template<typename L>
auto operator-(const Point_impl<L>& lhs, int rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x -= rhs;
    rv.y -= rhs;
    return rv;
}

template<typename L>
auto operator*(const Point_impl<L>& lhs, int rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x *= rhs;
    rv.y *= rhs;
    return rv;
}

template<typename L>
auto operator/(const Point_impl<L>& lhs, int rhs) {
    Point_impl<decltype(lhs.x)> rv = lhs;
    rv.x /= rhs;
    rv.y /= rhs;
    return rv;
}

//math functions
template<typename L>
L floor(const Point_impl<L>& lhs) {
    return Point_impl<L>(floor(lhs.x), floor(lhs.y));
}

template<typename L>
L round(const Point_impl<L>& lhs) {
    return Point_impl<L>(round(lhs.x), round(lhs.y));
}

using PointI = Point_impl<int>;
using PointF = Point_impl<float>;