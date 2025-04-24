#pragma once 

#include <chrono>
#include <sstream>
#include <stdexcept>
#include <iostream>

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

    std::string toString() const;
    float toFloat() const;

    Time operator+(const Time& other) const;
    Time operator-(const Time& other) const;
    const Time& operator+=(const Time& other);
    const Time& operator-=(const Time& other);
    const Time& operator=(const Time& other);
};

std::ostream& operator<<(std::ostream& os, const Time& time);