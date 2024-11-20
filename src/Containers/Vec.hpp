#pragma once

#include "defines.hpp"
#include <cmath>

template <typename T>
class Vec2 {
   public:
    T x;
    T y;

    Vec2() {}

    Vec2(T X, T Y) : x(X), y(Y) {}

    Vec2<T>& add(const Vec2<T>& vec2) {
        x += vec2.x;
        y += vec2.y;

        return *this;
    }

    Vec2<T>& multiply(const f32 scale) {
        x *= scale;
        y *= scale;

        return *this;
    }

    Vec2<T>& normalize() {
        T vec_length = length();
        x /= vec_length;
        y /= vec_length;
        return *this;
    }

    T length() const {
        return (T)sqrtf((y * y) + (x * x));
    }

    Vec2<T> operator+=(const Vec2<T>& rhs) const {
        return Vec2<T>(x + rhs.x, y + rhs.y);
    }

    Vec2<T> operator-(const Vec2<T>& rhs) const {
        return Vec2<T>(x - rhs.x, y - rhs.y);
    }

    Vec2<T> operator+(const Vec2<T>& rhs) const {
        return Vec2<T>(x + rhs.x, y + rhs.y);
    }

    Vec2<T> operator*(const f32 rhs) const {
        return Vec2<T>(x * rhs, y * rhs);
    }

    T operator*(const Vec2<T> rhs) const {
        return (x * rhs.x) + (y * rhs.y);
    }
};

using Vec2f = Vec2<f32>;