#pragma once

#include <set>

enum class RailEventType {
    StationClose,
    RailClose
};

class RailEventListener {
public:
    virtual ~RailEventListener() = default;
    virtual void onRailEvent(RailEventType eventType) = 0;
};

class RailEventSource {
private:
    std::set<RailEventListener*> observers;
protected:
    void notifyObservers(RailEventType eventType) {
        for (auto observer : observers) {
            observer->onRailEvent(eventType);
        }
    }
public:
    virtual ~RailEventSource() = default;
    void addObserver(RailEventListener* observer) { observers.insert(observer); }
    void removeObserver(RailEventListener* observer) { observers.erase(observer); }
};