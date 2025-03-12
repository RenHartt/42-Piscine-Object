#pragma once

template <typename T>
class Singleton {
protected:
    Singleton() {}
    ~Singleton() {}

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& getInstance() {
        static T instance;
        return instance;
    }
};