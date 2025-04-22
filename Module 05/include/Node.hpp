#pragma once

#include <unordered_set>
#include <string>
#include <stdexcept>

#include "Utils.hpp"
#include "LinkablePart.hpp"
#include "RailwayCollection.hpp"

class Rail;

class Node : public LinkablePart {
private:
    std::string name;
    std::unordered_set<Rail*> connectedSegments;
public:
    Node(const std::string& name) : name(name) {
        if (name.empty()) {
            throw std::invalid_argument("Node name cannot be empty");
        }
        NodeCollection::getInstance().add(this);
    }

    const std::string& getName() const { return name; }
    const std::unordered_set<Rail*>& getConnectedNodes() const { return connectedSegments; }
    
    void addConnection(Rail* segment) {
        if (segment == nullptr) {
            throw std::invalid_argument("Node cannot be null");
        }
        connectedSegments.insert(segment);
    }
    
    void removeConnection(Rail* segment) {
        if (segment == nullptr) {
            throw std::invalid_argument("Node cannot be null");
        }
        connectedSegments.erase(segment);
    }
};