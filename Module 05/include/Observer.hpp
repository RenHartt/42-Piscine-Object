#pragma once

#include <unordered_set>

#include "Time.hpp"

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const Time& time) = 0;
};

class Subject {
protected:
    std::unordered_set<Observer*> observers;
public:
    virtual ~Subject() = default;
    
    void attach(Observer* observer) { 
        observers.insert(observer);
    }

    void detach(Observer* observer) {
        observers.erase(observer);
    }

    void notify(const Time& time) {
        for (auto observer : observers) {
            observer->update(time);
        }
    }
};