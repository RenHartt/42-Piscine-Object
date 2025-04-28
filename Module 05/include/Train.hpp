#pragma once

#include <string>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "Time.hpp"
#include "Observer.hpp"
#include "RailwayCollection.hpp"
#include "LinkablePart.hpp"
#include "Node.hpp"
#include "Rail.hpp"

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
    float weightTonnes;
    float frictionCoefficient;
    float accelerationForce;
    float brakingForce;
    float accelerationCoefficient;
    float brakingCoefficient;
    float gravity = 9.81f;

public:
    Specification(float weightTonnes, float frictionCoefficient, float accelerationForce, float brakingForce)
        : weightTonnes(weightTonnes), frictionCoefficient(frictionCoefficient), accelerationForce(accelerationForce), brakingForce(brakingForce) {
        if (weightTonnes <= 0 || frictionCoefficient <= 0 || accelerationForce <= 0 || brakingForce <= 0) {
            throw std::invalid_argument("Weight, friction coefficient, acceleration force, and braking force must be positive");
        }

        float weightNewtons = weightTonnes * 1000;
        float mass = weightNewtons;
        float accelerationForceInNewtons = accelerationForce * 1000;
        float brakingForceInNewtons = brakingForce * 1000;
        float frictionForce = frictionCoefficient * mass * gravity;

        accelerationCoefficient = (accelerationForceInNewtons - frictionForce) / mass;
        brakingCoefficient = (brakingForceInNewtons + frictionForce) / mass;

        if (accelerationCoefficient < 0 || brakingCoefficient < 0) {
            throw std::invalid_argument("Acceleration and braking coefficients must be non-negative");
        }
    }

    float getWeightTonnes() const { return weightTonnes; }
    float getFrictionCoefficient() const { return frictionCoefficient; }
    float getAccelerationForce() const { return accelerationForce; }
    float getBrakingForce() const { return brakingForce; }
    float getAccelerationCoefficient() const { return accelerationCoefficient; }
    float getBrakingCoefficient() const { return brakingCoefficient; }
};

class Route {
private:
    Node* departure;
    Node* arrival;
    std::list<LinkablePart*> route;
public:
    Route(Node* departure, Node* arrival) : departure(departure), arrival(arrival) {
        if (departure == nullptr || arrival == nullptr) {
            throw std::invalid_argument("Departure or arrival node cannot be null");
        }
    }

    Node* getDeparture() const { return departure; }
    Node* getArrival() const { return arrival; }
    const std::list<LinkablePart*>& getRoute() const { return route; }
    void setRoute(const std::list<LinkablePart*>& newRoute) { route = newRoute; }
};

class Schedule {
private:
    Time departureTime;
    Time stopDuration;
    Time countdown = stopDuration;
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
    const Time& getCountdown() const { return countdown; }
    void setCountdown(const Time& newCountdown) { countdown = newCountdown; }
};

enum class TrainStateType {
    Accelerate,
    ConstantSpeed,
    Decelerate,
    Stop
};

std::ostream& operator<<(std::ostream& os, TrainStateType state);

class TrainState {
private:
    TrainStateType stateType = TrainStateType::Stop;
    LinkablePart* currentPart;
    float speed = 0.0f; // Initial speed in m/s
    float distanceOnSegment = 0.0f;
public:
    TrainState(LinkablePart* part) : currentPart(part) {
        if (part == nullptr) {
            throw std::invalid_argument("Current part cannot be null");
        }
    }

    TrainStateType getStateType() const { return stateType; }
    LinkablePart* getCurrentPart() const { return currentPart; }
    float getSpeed() const { return speed; }
    float getDistance() const { return distanceOnSegment; }

    void setStateType(TrainStateType newState) { stateType = newState; }
    void setSegment(LinkablePart* part) { currentPart = part; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setDistance(float distance) { distanceOnSegment = distance; }
};

class FileLogger {
private:
    std::string folder = "logs";
    std::fstream logFile;
public:
    FileLogger(const std::string& filename) {
        if (!std::filesystem::exists(folder)) {
            std::filesystem::create_directory(folder);
        }
        std::string fullPath = folder + "/" + filename;
        logFile.open(fullPath, std::ios::out | std::ios::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file");
        }
    }

    ~FileLogger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void write(const std::string& message) {
        if (logFile.is_open()) {
            logFile << message << std::endl;
        }
    }
};

class Train : public Observer {
private:
    Identity identity;
    Specification specification;
    Route route;
    Schedule schedule;
    TrainState state;
    FileLogger logger;
public:
    Train(const std::string& name, float weight, float frictionCoefficient, float accelerationForce, float brakingForce,
          Node* departure, Node* arrival, const Time& departureTime, const Time& stopDuration)
        : identity(name), specification(weight, frictionCoefficient, accelerationForce, brakingForce),
          route(departure, arrival), schedule(departureTime, stopDuration), state(departure), 
          logger(name + "_" + departureTime.toString() + ".result") {
            TrainCollection::getInstance().add(this);
    }

    long long getId() const { return identity.getId(); }
    const std::string& getName() const { return identity.getName(); }
    float getWeightTonnes() const { return specification.getWeightTonnes(); }
    float getFrictionCoefficient() const { return specification.getFrictionCoefficient(); }
    float getAccelerationForce() const { return specification.getAccelerationForce(); }
    float getBrakingForce() const { return specification.getBrakingForce(); }
    float getAccelerationCoefficient() const { return specification.getAccelerationCoefficient(); }
    float getBrakingCoefficient() const { return specification.getBrakingCoefficient(); }
    Node* getDeparture() const { return route.getDeparture(); }
    Node* getArrival() const { return route.getArrival(); }
    const std::list<LinkablePart*>& getRoute() const { return route.getRoute(); }
    const Time& getDepartureTime() const { return schedule.getDepartureTime(); }
    const Time& getStopDuration() const { return schedule.getStopDuration(); }
    const Time& getCountdown() const { return schedule.getCountdown(); }
    LinkablePart* getCurrentPart() const { return state.getCurrentPart(); }
    float getDistanceOnSegment() const { return state.getDistance(); }
    float getSpeed() const { return state.getSpeed(); }
    TrainStateType getStateType() const { return state.getStateType(); }
    void log();

    void setCountdown(const Time& newCountdown) { schedule.setCountdown(newCountdown); }
    void setCurrentPart(LinkablePart* part) {
        if (Rail* rail = dynamic_cast<Rail*>(getCurrentPart())) {
            rail->removeTrain(this);
        }
        state.setSegment(part);
        if (Rail* rail = dynamic_cast<Rail*>(part)) {
            rail->addTrain(this);
        }
    }
    void setSpeed(float newSpeed) { state.setSpeed(newSpeed); }
    void setDistanceOnSegment(float distance) { state.setDistance(distance); }
    void setRoute(const std::list<LinkablePart*>& newRoute) { route.setRoute(newRoute); }

    float calculateBrakingDistance() const {
        float velocity = state.getSpeed();
        float brakingDeceleration = getBrakingCoefficient();
        return (velocity * velocity) / (2 * brakingDeceleration);
    }

    void requestRoute();
    LinkablePart* getNextPart();
    void travelOnRail(const Time& time);
    void travelOnNode(const Time& time);
    void travel(const Time& time);
    void update(const Time& time) override;
};