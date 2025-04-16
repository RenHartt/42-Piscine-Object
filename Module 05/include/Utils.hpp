#pragma once

#include <chrono>

struct Vec2f {
    float x, y;

    Vec2f(float x = 0, float y = 0) : x(x), y(y) {}
    Vec2f(const Vec2f& other) { *this = other; }
    ~Vec2f() {}
    
    Vec2f& operator=(const float arr[2]) {
        x = arr[0];
        y = arr[1];
        return *this;
    }

    Vec2f& operator=(const Vec2f& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }

    Vec2f operator+(const Vec2f& other) const {
        return Vec2f(x + other.x, y + other.y);
    }

    Vec2f operator-(const Vec2f& other) const {
        return Vec2f(x - other.x, y - other.y);
    }

    Vec2f operator*(float scalar) const {
        return Vec2f(x * scalar, y * scalar);
    }

    Vec2f operator/(float scalar) const {
        return Vec2f(x / scalar, y / scalar);
    }

    float dot(const Vec2f& other) const {
        return x * other.x + y * other.y;
    }
};

struct Time {
    std::chrono::hours hours;
    std::chrono::minutes minutes;
    std::chrono::seconds seconds;

    Time(int h = 0, int m = 0, int s = 0) : hours(h), minutes(m), seconds(s) {}
};