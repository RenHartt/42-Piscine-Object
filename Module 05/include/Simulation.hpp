#pragma once

#include "Singleton.hpp"
#include "RailwayCollection.hpp"
#include "Node.hpp"
#include "Rail.hpp"
#include "Train.hpp"
#include "Factory.hpp"

#include <fstream>
#include <stdexcept>
#include <sstream>

class Simulation : public Singleton<Simulation> {
private:

public:
    Simulation() = default;
    ~Simulation() = default;

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
                Factory::createNode(name);
            } else if (type == "Rail") {
                std::string departureName, arrivalName;
                float length, speedLimit;
                iss >> departureName >> arrivalName >> length >> speedLimit;
                Node* departure = NodeCollection::getInstance().getByName(departureName);
                Node* arrival = NodeCollection::getInstance().getByName(arrivalName);
                if (!departure || !arrival) {
                    throw std::runtime_error("Invalid node names: " + departureName + ", " + arrivalName);
                }
                Factory::createRail(departure, arrival, length, speedLimit);
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
            Factory::createTrain(name, weight, friction, acceleration, brake, departure, arrival, departureTime, stopDuration);
        }
    }
};