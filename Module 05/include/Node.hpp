#pragma once

#include <unordered_set>
#include <string>
#include <stdexcept>

#include "Utils.hpp"
#include "LinkablePart.hpp"
#include "RailwayCollection.hpp"
#include "Event.hpp"

class Node : public LinkablePart, public NodeEventListener {
private:
    std::string name;
    bool isClosed = false;
public:
    Node(const std::string& name) : name(name) {
        if (name.empty()) {
            throw std::invalid_argument("Node name cannot be empty");
        }
        NodeCollection::getInstance().add(this);
    }

    const std::string& getName() const { return name; }
    std::unordered_set<Rail*> getConnectedRails() const { return castToSet<Rail>(connectedParts); }
    void onNodeEvent(NodeEventType eventType) override {
        if (eventType == NodeEventType::NodeClose) {
            isClosed = true;
        } else if (eventType == NodeEventType::NodeOpen) {
            isClosed = false;
        }
    }
};