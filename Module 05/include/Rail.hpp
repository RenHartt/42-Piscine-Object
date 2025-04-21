#pragma once

#include "Node.hpp"
#include "Event.hpp"
#include "LinkablePart.hpp"
#include "RailwayCollection.hpp"

#include <unordered_set>
#include <stdexcept>

class Rail : public LinkablePart, public RailEventSource {
private:
    inline static long long nextId = 1;
    long long id;
    const Node* departure;
    const Node* arrival;
    float length;
    float speedLimit;
    std::unordered_set<long long> trainOnSegment;
public:
    Rail(Node* departure, Node* arrival, float length, float speedLimit)
        : id(nextId++), departure(departure), arrival(arrival), length(length), speedLimit(speedLimit) {
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
    const Node* getDeparture() const { return departure; }
    const Node* getArrival() const { return arrival; }
    float getLength() const { return length; }
    float getSpeedLimit() const { return speedLimit; }

    void addTrain(long long trainId) { trainOnSegment.insert(trainId); }
    void removeTrain(long long trainId) { trainOnSegment.erase(trainId); }
    bool isTrainOnSegment(long long trainId) const { return trainOnSegment.find(trainId) != trainOnSegment.end(); }
    const std::unordered_set<long long>& getTrainsOnSegment() const { return trainOnSegment; }
    void clearTrainsOnSegment() { trainOnSegment.clear(); }
    bool isSegmentEmpty() const { return trainOnSegment.empty(); }
};