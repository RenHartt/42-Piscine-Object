#pragma once

template <typename T>
class Singleton {
protected:
    Singleton() {}
    ~Singleton() {}

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    Singleton(T&&) = delete;
    Singleton& operator=(T&&) = delete;
    Singleton(const T&) = delete;
    Singleton& operator=(const T&) = delete;
    Singleton(T&) = delete;
    Singleton& operator=(T&) = delete;

    static T& getInstance() {
        static T instance;
        return instance;
    }
};