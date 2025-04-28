#include "Time.hpp"

std::string Time::toString() const {
    std::ostringstream oss;
    oss << hours.count() << ":" << minutes.count() << ":" << seconds.count();
    return oss.str();
}

float Time::toFloat() const {
    return hours.count() * 3600 + minutes.count() * 60 + seconds.count();
}

Time Time::operator+(const Time& other) const {
    float totalSeconds = this->toFloat() + other.toFloat();
    int h = static_cast<int>(totalSeconds / 3600);
    int m = static_cast<int>((totalSeconds - h * 3600) / 60);
    int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
    return Time(h, m, s);
}

Time Time::operator-(const Time& other) const {
    float totalSeconds = this->toFloat() - other.toFloat();
    int h = static_cast<int>(totalSeconds / 3600);
    int m = static_cast<int>((totalSeconds - h * 3600) / 60);
    int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
    return Time(h, m, s);
}

const Time& Time::operator+=(const Time& other) {
    float totalSeconds = this->toFloat() + other.toFloat();
    int h = static_cast<int>(totalSeconds / 3600);
    int m = static_cast<int>((totalSeconds - h * 3600) / 60);
    int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
    this->hours = std::chrono::hours(h);
    this->minutes = std::chrono::minutes(m);
    this->seconds = std::chrono::seconds(s);
    return *this;
}

const Time& Time::operator-=(const Time& other) {
    float totalSeconds = this->toFloat() - other.toFloat();
    int h = static_cast<int>(totalSeconds / 3600);
    int m = static_cast<int>((totalSeconds - h * 3600) / 60);
    int s = static_cast<int>(totalSeconds - h * 3600 - m * 60);
    this->hours = std::chrono::hours(h);
    this->minutes = std::chrono::minutes(m);
    this->seconds = std::chrono::seconds(s);
    return *this;
}

const Time& Time::operator=(const Time& other) {
    this->hours = other.hours;
    this->minutes = other.minutes;
    this->seconds = other.seconds;
    return *this;
}

bool Time::operator<(const Time& other) const {
    return this->toFloat() < other.toFloat();
}

bool Time::operator>(const Time& other) const {
    return this->toFloat() > other.toFloat();
}

bool Time::operator<=(const Time& other) const {
    return this->toFloat() <= other.toFloat();
}

bool Time::operator>=(const Time& other) const {
    return this->toFloat() >= other.toFloat();
}

bool Time::operator==(const Time& other) const {
    return this->toFloat() == other.toFloat();
}

bool Time::operator!=(const Time& other) const {
    return this->toFloat() != other.toFloat();
}
