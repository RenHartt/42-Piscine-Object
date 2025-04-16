#pragma once

#include <string>

#include "Node.hpp"
#include "Utils.hpp"

class Identity {
private:
    static long long nextId;
    long long id;
    std::string name;
public:
    Identity(const std::string& name) : id(nextId++), name(name) {}

    long long getId() const { return id; }
    const std::string& getName() const { return name; }

    void setName(const std::string& name) { this->name = name; }
};

long long Identity::nextId = 1;

class Specification {
private:
    float weight;
    float frictionCoefficient;
    float accelerationForce;
    float brakingForce;
public:
    Specification(float weight, float frictionCoefficient, float accelerationForce, float brakingForce)
        : weight(weight), frictionCoefficient(frictionCoefficient), accelerationForce(accelerationForce), brakingForce(brakingForce) {}

    float getWeight() const { return weight; }
    float getFrictionCoefficient() const { return frictionCoefficient; }
    float getAccelerationForce() const { return accelerationForce; }
    float getBrakingForce() const { return brakingForce; }

    void setWeight(float weight) { this->weight = weight; }
    void setFrictionCoefficient(float frictionCoefficient) { this->frictionCoefficient = frictionCoefficient; }
    void setAccelerationForce(float accelerationForce) { this->accelerationForce = accelerationForce; }
    void setBrakingForce(float brakingForce) { this->brakingForce = brakingForce; }
};

class Route {
private:
    Node departure, arrival;
public:
    Route(const Node& departure, const Node& arrival) : departure(departure), arrival(arrival) {}

    const Node& getDeparture() const { return departure; }
    const Node& getArrival() const { return arrival; }

    void setDeparture(const Node& departure) { this->departure = departure; }
    void setArrival(const Node& arrival) { this->arrival = arrival; }
};

class Schedule {
private:
    Time departureTime, stopDuration;
public:
    Schedule(Time departureTime, Time stopDuration)
        : departureTime(departureTime), stopDuration(stopDuration) {}

    Time getDepartureTime() const { return departureTime; }
    Time getStopDuration() const { return stopDuration; }

    void setDepartureTime(Time departureTime) { this->departureTime = departureTime; }
    void setStopDuration(Time stopDuration) { this->stopDuration = stopDuration; }
};

class Train {
private:
    Identity identity;
    Specification specification;
    Route route;
    Schedule schedule;
public:
    Train(const std::string& name, float weight, float frictionCoefficient, float accelerationForce, float brakingForce,
          const Node& departure, const Node& arrival, Time departureTime, Time stopDuration)
        : identity(name), specification(weight, frictionCoefficient, accelerationForce, brakingForce),
          route(departure, arrival), schedule(departureTime, stopDuration) {}

    const std::string& getName() const { return identity.getName(); }
    float getWeight() const { return specification.getWeight(); }
    float getFrictionCoefficient() const { return specification.getFrictionCoefficient(); }
    float getAccelerationForce() const { return specification.getAccelerationForce(); }
    float getBrakingForce() const { return specification.getBrakingForce(); }
    const Node& getDeparture() const { return route.getDeparture(); }
    const Node& getArrival() const { return route.getArrival(); }
    Time getDepartureTime() const { return schedule.getDepartureTime(); }
    Time getStopDuration() const { return schedule.getStopDuration(); }

    void setName(const std::string& name) { identity.setName(name); }
    void setWeight(float weight) { specification.setWeight(weight); }
    void setFrictionCoefficient(float frictionCoefficient) { specification.setFrictionCoefficient(frictionCoefficient); }
    void setAccelerationForce(float accelerationForce) { specification.setAccelerationForce(accelerationForce); }
    void setBrakingForce(float brakingForce) { specification.setBrakingForce(brakingForce); }
    void setDeparture(const Node& departure) { route.setDeparture(departure); }
    void setArrival(const Node& arrival) { route.setArrival(arrival); }
    void setDepartureTime(Time departureTime) { schedule.setDepartureTime(departureTime); }
    void setStopDuration(Time stopDuration) { schedule.setStopDuration(stopDuration); }
};