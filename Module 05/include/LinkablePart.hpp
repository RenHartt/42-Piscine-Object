#pragma once

#include <unordered_set>

class LinkablePart {
protected:
    std::unordered_set<LinkablePart*> connectedParts;
public:
    LinkablePart() = default;
    LinkablePart(std::unordered_set<LinkablePart*> connectedParts) : connectedParts(connectedParts) {}
    virtual ~LinkablePart() = default;

    void addConnection(LinkablePart* part) {
        if (part == nullptr) {
            throw std::invalid_argument("LinkablePart cannot be null");
        }
        connectedParts.insert(part);
    }

    const std::unordered_set<LinkablePart*>& getConnectedParts() const { return connectedParts; }
};