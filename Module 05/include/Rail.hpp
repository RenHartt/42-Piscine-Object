#pragma once

#include "Node.hpp"
#include "Event.hpp"
#include "LinkablePart.hpp"
#include "RailwayCollection.hpp"
#include "Utils.hpp"

#include <unordered_set>
#include <stdexcept>

class Rail : public LinkablePart, public RailEventListener {
private:
    inline static long long nextId = 1;
    long long id;
    float length;
    float speedLimit;
    std::unordered_set<Train*> trainOnSegment;
    bool isClosed = false;
public:
    Rail(Node* departure, Node* arrival, float length, float speedLimit)
        : LinkablePart({departure, arrival}), id(nextId++), length(length), speedLimit(speedLimit) {
        if (departure == nullptr || arrival == nullptr) {
            throw std::invalid_argument("Departure or arrival node cannot be null");
        }
        if (departure == arrival) {
            throw std::invalid_argument("Departure and arrival nodes cannot be the same");
        }
        if (length <= 0) {
            throw std::invalid_argument("Length must be positive");
        }
        if (speedLimit <= 0) {
            throw std::invalid_argument("Speed limit must be positive");
        }
        departure->addConnection(this);
        arrival->addConnection(this);
        RailCollection::getInstance().add(this);
    }

    long long getId() const { return id; }
    Node* getDeparture() const { return dynamic_cast<Node*>(*(++connectedParts.begin())); }
    Node* getArrival() const { return dynamic_cast<Node*>(*connectedParts.begin()); }
    std::unordered_set<Node*> getConnectedNodes() const { return castToSet<Node>(connectedParts); }
    float getLength() const { return length; }
    float getSpeedLimit() const { return speedLimit; }
    bool isClosedRail() const { return isClosed; }

    void addTrain(Train* train) { trainOnSegment.insert(train); }
    void removeTrain(Train* train) { trainOnSegment.erase(train); }
    bool isTrainOnSegment(Train* train) const { return trainOnSegment.find(train) != trainOnSegment.end(); }
    const std::unordered_set<Train*>& getTrainsOnSegment() const { return trainOnSegment; }
    void clearTrainsOnSegment() { trainOnSegment.clear(); }
    bool isSegmentEmpty() const { return trainOnSegment.empty(); }
    void onRailEvent(RailEventType eventType) override {
        if (eventType == RailEventType::RailClose) {
            isClosed = true;
            // std::cout << "Rail " << id << " is closed." << std::endl;
        } else if (eventType == RailEventType::RailOpen) {
            isClosed = false;
            // std::cout << "Rail " << id << " is open." << std::endl;
        }
    }
};