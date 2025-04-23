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
public:
    Node(const std::string& name) : name(name) {
        if (name.empty()) {
            throw std::invalid_argument("Node name cannot be empty");
        }
        NodeCollection::getInstance().add(this);
    }

    const std::string& getName() const { return name; }
    std::unordered_set<Rail*> getConnectedRails() const { return castToSet<Rail>(connectedParts); }
};