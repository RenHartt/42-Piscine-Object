#pragma once

#include <chrono>
#include <sstream>

struct Time {
    std::chrono::hours hours;
    std::chrono::minutes minutes;
    std::chrono::seconds seconds;

    Time(int h = 0, int m = 0, int s = 0)
    : hours(h), minutes(m), seconds(s) {}
    Time(const std::string& hours) {
        std::istringstream iss(hours);
        char delimiter;
        int h, m;
        iss >> h >> delimiter >> m;
        this->hours = std::chrono::hours(h);
        this->minutes = std::chrono::minutes(m);
        this->seconds = std::chrono::seconds(0);
        if (h < 0 || m < 0 || m >= 60) {
            throw std::invalid_argument("Invalid time format");
        }
    }
    Time(const Time& other) {
        *this = other;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << hours.count() << ":" << minutes.count() << ":" << seconds.count();
        return oss.str();
    }

    float toFloat() const {
        return hours.count() * 3600 + minutes.count() * 60 + seconds.count();
    }

    Time operator+(const Time& other) const {
        float totalSeconds = this->toFloat() + other.toFloat();
        int h = static_cast<int>(totalSeconds / 3600);
        int m = static_cast<int>((totalSeconds - h * 3600) / 60);
        int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
        return Time(h, m, s);
    }

    Time operator-(const Time& other) const {
        float totalSeconds = this->toFloat() - other.toFloat();
        int h = static_cast<int>(totalSeconds / 3600);
        int m = static_cast<int>((totalSeconds - h * 3600) / 60);
        int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
        return Time(h, m, s);
    }

    const Time& operator+=(const Time& other) {
        float totalSeconds = this->toFloat() + other.toFloat();
        int h = static_cast<int>(totalSeconds / 3600);
        int m = static_cast<int>((totalSeconds - h * 3600) / 60);
        int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
        this->hours = std::chrono::hours(h);
        this->minutes = std::chrono::minutes(m);
        this->seconds = std::chrono::seconds(s);
        return *this;
    }
    
    const Time& operator-=(const Time& other) {
        float totalSeconds = this->toFloat() - other.toFloat();
        int h = static_cast<int>(totalSeconds / 3600);
        int m = static_cast<int>((totalSeconds - h * 3600) / 60);
        int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
        this->hours = std::chrono::hours(h);
        this->minutes = std::chrono::minutes(m);
        this->seconds = std::chrono::seconds(s);
        return *this;
    }

    const Time& operator=(const Time& other) {
        this->hours = other.hours;
        this->minutes = other.minutes;
        this->seconds = other.seconds;
        return *this;
    }
};