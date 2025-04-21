#include "RailwayCollection.hpp"
#include "Train.hpp"
#include "Rail.hpp"
#include "Node.hpp"

#include <iostream>

TrainCollection::~TrainCollection() {
    for (auto& train : elements) {
        delete train;
    }
}

void TrainCollection::printItem(Train* item) const {
    std::cout << "Id : " << item->getId() << ", Name: " << item->getName() << std::endl;
    std::cout << "Weight: " << item->getWeight() << ", Friction Coefficient: " << item->getFrictionCoefficient()
                << ", Acceleration Force: " << item->getAccelerationForce() << ", Braking Force: " << item->getBrakingForce()
                << std::endl;
    std::cout << "Departure: " << item->getDeparture()->getName() << ", Arrival: " << item->getArrival()->getName() << std::endl;
    std::cout << "Departure Time: " << item->getDepartureTime().hours.count() << ":" << item->getDepartureTime().minutes.count()
                << ", Stop Duration: " << item->getStopDuration().hours.count() << ":" << item->getStopDuration().minutes.count() << std::endl;
    std::cout << "Motion Phase: " << static_cast<int>(item->getPhase()) << ", Speed: " << item->getSpeed() << std::endl;
}

RailCollection::~RailCollection() {
    for (auto& rail : elements) {
        delete rail;
    }
}

void RailCollection::printItem(Rail* item) const {
    std::cout << "Id: " << item->getId() << ", Departure: " << item->getDeparture()->getName()
                << ", Arrival: " << item->getArrival()->getName() << std::endl;
    std::cout << "Length: " << item->getLength() << ", Speed Limit: " << item->getSpeedLimit() << std::endl;
}

NodeCollection::~NodeCollection() {
    for (auto& node : elements) {
        delete node;
    }
}

void NodeCollection::printItem(Node* item) const {
    std::cout << "Node Name: " << item->getName() << std::endl;
    std::cout << "Connected Segments: ";
    for (const auto& segment : item->getConnectedNodes()) {
        std::cout << segment->getId() << " ";
    }
    std::cout << std::endl;
}