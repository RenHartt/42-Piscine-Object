#pragma once

#include <set>

enum class MotionPhase {
    Stopped,
    Moving,
    Braking,
    Accelerating
};

class MotionListener {
public:
    virtual ~MotionListener() = default;
    virtual void onMotionPhase(MotionPhase state) = 0;
};

class MotionController {
private:
    std::set<MotionListener*> observers;
protected:
    void notifyMovementObservers(MotionPhase state) {
        for (auto observer : observers) {
            observer->onMotionPhase(state);
        }
    }
public:
virtual ~MotionController() = default;
    void addMovementObserver(MotionListener* observer) { observers.insert(observer); }
    void removeMovementObserver(MotionListener* observer) { observers.erase(observer); }
};