#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include "Node.hpp"
#include "Utils.hpp"
#include "Event.hpp"
#include "Motion.hpp"
#include "Rail.hpp"
#include "RailwayCollection.hpp"

class Identity {
private:
    inline static long long nextId = 1;
    long long id;
    std::string name;
public:
    Identity(const std::string& name) : id(nextId++), name(name) {}
    Identity(const Identity& other) = delete;
    Identity& operator=(const Identity& other) = delete;
    Identity(Identity&& other) = delete;
    Identity& operator=(Identity&& other) = delete;

    long long getId() const { return id; }
    const std::string& getName() const { return name; }
};

class Specification {
private:
    float weight;
    float frictionCoefficient;
    float accelerationForce;
    float brakingForce;
public:
    Specification(float weight, float frictionCoefficient, float accelerationForce, float brakingForce)
        : weight(weight), frictionCoefficient(frictionCoefficient), accelerationForce(accelerationForce), brakingForce(brakingForce) {
        if (weight <= 0 || frictionCoefficient <= 0 || accelerationForce <= 0 || brakingForce <= 0) {
            throw std::invalid_argument("Weight, friction coefficient, acceleration force, and braking force must be positive");
        }
    }

    float getWeight() const { return weight; }
    float getFrictionCoefficient() const { return frictionCoefficient; }
    float getAccelerationForce() const { return accelerationForce; }
    float getBrakingForce() const { return brakingForce; }
};

class Route {
private:
    const Node* departure;
    const Node* arrival;
    std::vector<LinkablePart*> route;
public:
    Route(const Node* departure, const Node* arrival) : departure(departure), arrival(arrival) {
        if (departure == nullptr || arrival == nullptr) {
            throw std::invalid_argument("Departure or arrival node cannot be null");
        }
    }

    const Node* getDeparture() const { return departure; }
    const Node* getArrival() const { return arrival; }
    const std::vector<LinkablePart*>& getRoute() const { return route; }
    void setRoute(const std::vector<LinkablePart*>& newRoute) {
        route = newRoute;
    }
};

class Schedule {
private:
    Time departureTime;
    Time stopDuration;
public:
    Schedule(const Time& departureTime, const Time& stopDuration)
        : departureTime(departureTime), stopDuration(stopDuration) {
        if (stopDuration.hours.count() < 0 || stopDuration.minutes.count() < 0 || stopDuration.seconds.count() < 0) {
            throw std::invalid_argument("Stop duration cannot be negative");
        }
        if (departureTime.hours.count() < 0 || departureTime.minutes.count() < 0 || departureTime.seconds.count() < 0) {
            throw std::invalid_argument("Departure time cannot be negative");
        }
    }

    const Time& getDepartureTime() const { return departureTime; }
    const Time& getStopDuration() const { return stopDuration; }
};

class TrainState : public MotionListener, public RailEventListener {
private:
    MotionPhase phase = MotionPhase::Stopped;
    float speed = 0.0f;
    const Rail* currentSegment = nullptr;
    float distanceOnSegment = 0.0f;
public:
    void onMotionPhase(MotionPhase p) override {
        phase = p;
        switch (p) {
            case MotionPhase::Stopped:
                speed = 0.0f;
                break;
            case MotionPhase::Moving:
                // handle moving state
                break;
            case MotionPhase::Braking:
                // handle braking state
                break;
            case MotionPhase::Accelerating:
                // handle accelerating state
                break;
        }
    }

    void onRailEvent(RailEventType e) override {
        switch (e) {
            case RailEventType::StationClose:
                // handle station close event
                break;
            case RailEventType::RailClose:
                // handle rail segment close event
                break;
        }
    }

    MotionPhase getPhase() const { return phase; }
    float getSpeed() const { return speed; }
    const Rail* getSegment() const { return currentSegment; }
    float getDistance() const { return distanceOnSegment; }

    void advance(float dt) {
        distanceOnSegment += speed * dt;
        // if exceeding segment length: notify and change segment externally
    }
};

class Train {
private:
    Identity identity;
    Specification specification;
    Route route;
    Schedule schedule;
    TrainState state;
public:
    Train(const std::string& name, float weight, float frictionCoefficient, float accelerationForce, float brakingForce,
          Node* departure, Node* arrival, const Time& departureTime, const Time& stopDuration)
        : identity(name), specification(weight, frictionCoefficient, accelerationForce, brakingForce),
          route(departure, arrival), schedule(departureTime, stopDuration), state() {
            TrainCollection::getInstance().add(this);
          }

    long long getId() const { return identity.getId(); }
    const std::string& getName() const { return identity.getName(); }
    float getWeight() const { return specification.getWeight(); }
    float getFrictionCoefficient() const { return specification.getFrictionCoefficient(); }
    float getAccelerationForce() const { return specification.getAccelerationForce(); }
    float getBrakingForce() const { return specification.getBrakingForce(); }
    const Node* getDeparture() const { return route.getDeparture(); }
    const Node* getArrival() const { return route.getArrival(); }
    const Time& getDepartureTime() const { return schedule.getDepartureTime(); }
    const Time& getStopDuration() const { return schedule.getStopDuration(); }
    MotionPhase getPhase() const { return state.getPhase(); }
    const Rail* getCurrentSegment() const { return state.getSegment(); }
    float getDistanceOnSegment() const { return state.getDistance(); }
    float getSpeed() const { return state.getSpeed(); }
};