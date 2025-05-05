#pragma once

#include "Singleton.hpp"
#include "Observer.hpp"
#include "Factory.hpp"
#include "RailwayCollection.hpp"
#include "Pathfinding.hpp"
#include "Train.hpp"
#include "Utils.hpp"

#include <fstream>
#include <stdexcept>
#include <sstream>

class Simulation :
    public Singleton<Simulation>, public Subject {
private:
    Time globalTime = Time(0, 0, 0);
public:
    Simulation() = default;
    ~Simulation() = default;

    const Time& getGlobalTime() const { return globalTime; }
    void setGlobalTime(const Time& time) { globalTime = time; }

    static void parseRailNetwork(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath);
        }
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string type;
            iss >> type;
            if (type == "Node") {
                std::string name;
                iss >> name;
                Factory::getInstance().createNode(name);
            } else if (type == "Rail") {
                std::string departureName, arrivalName;
                float length = 0, speedLimit = 0;
                iss >> departureName >> arrivalName >> length >> speedLimit;
                Node* departure = NodeCollection::getInstance().getByName(departureName);
                Node* arrival = NodeCollection::getInstance().getByName(arrivalName);
                if (!departure || !arrival) {
                    throw std::runtime_error("Invalid node names: " + departureName + ", " + arrivalName);
                }
                if (!length || !speedLimit) {
                    throw std::runtime_error("Invalid length or speed limit: " + std::to_string(length) + ", " + std::to_string(speedLimit));
                }
                Factory::getInstance().createRail(departure, arrival, length * 1000, speedLimit * (5./18.));
            } else {
                throw std::runtime_error("Unknown type: " + type);
            }
        }
    }

    static void parseTrainComposition(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filePath);
        }
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name;
            float weight, friction, acceleration, brake;
            std::string departureName, arrivalName;
            std::string hourOfDeparture, durationOfStop;
            iss >> name >> weight >> friction >> acceleration >> brake >> departureName >> arrivalName >> hourOfDeparture >> durationOfStop;
            Node* departure = NodeCollection::getInstance().getByName(departureName);
            Node* arrival = NodeCollection::getInstance().getByName(arrivalName);
            if (!departure || !arrival) {
                throw std::runtime_error("Invalid node names: " + departureName + ", " + arrivalName);
            }
            Time departureTime(hourOfDeparture);
            Time stopDuration(durationOfStop);
            Factory::getInstance().createTrain(name, weight, friction, acceleration, brake, departure, arrival, departureTime, stopDuration);
        }
    }

    const std::list<LinkablePart*> calculateRoute(Train* train) const {
        return Pathfinding().dijkstra(train);
    }

    void update(const Time& time) {
        globalTime += time;
        notify(time);
    }
};