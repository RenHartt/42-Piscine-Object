#pragma once

template<typename T>
class Singleton {
private:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(const Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    Singleton(const T&) = delete;
    Singleton& operator=(const T&) = delete;
    Singleton(const T&&) = delete;
    Singleton& operator=(const T&&) = delete;
public:
    Singleton() = default;
    ~Singleton() = default;
    
    static T& getInstance() {
        static T instance;
        return instance;
    }
};