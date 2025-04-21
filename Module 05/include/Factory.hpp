#pragma once

#include "Singleton.hpp"
#include "Train.hpp"
#include "Rail.hpp"
#include "Node.hpp"

class Factory : public Singleton<Factory> {
private:
    friend class Simulation;
    static Train* createTrain(const std::string& name, float weight, float frictionCoefficient, float accelerationForce, float brakingForce,
                       Node* departure, Node* arrival, const Time& departureTime, const Time& stopDuration) {
        return new Train(name, weight, frictionCoefficient, accelerationForce, brakingForce, departure, arrival, departureTime, stopDuration);
    }

    static Rail* createRail(Node* departure, Node* arrival, float length, float speedLimit) {
        return new Rail(departure, arrival, length, speedLimit);
    }

    static Node* createNode(const std::string& name) {
        return new Node(name);
    }
};