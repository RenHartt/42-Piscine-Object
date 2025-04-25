#pragma once

#include <set>

enum class RailEventType {
    RailClose,
    RailOpen
};

class RailEventListener {
public:
    virtual ~RailEventListener() = default;
    virtual void onRailEvent(RailEventType eventType) = 0;
};

class RailEventSource {
protected:
    std::set<RailEventListener*> railObservers;
public:
    virtual ~RailEventSource() = default;
    void addRailObserver(RailEventListener* railobserver) { railObservers.insert(railobserver); }
    void removeRailObserver(RailEventListener* railobserver) { railObservers.erase(railobserver); }
    void notifyRailObservers(RailEventType eventType) {
        for (auto observer : railObservers) {
            observer->onRailEvent(eventType);
        }
    }
};

enum class NodeEventType {
    NodeClose,
    NodeOpen
};

class NodeEventListener {
public:
    virtual ~NodeEventListener() = default;
    virtual void onNodeEvent(NodeEventType eventType) = 0;
};

class NodeEventSource {
protected:
    std::set<NodeEventListener*> nodeObservers;
public:
    virtual ~NodeEventSource() = default;
    void addNodeObserver(NodeEventListener* nodeobserver) { nodeObservers.insert(nodeobserver); }
    void removeNodeObserver(NodeEventListener* nodeobserver) { nodeObservers.erase(nodeobserver); }
    void notifyNodeObservers(NodeEventType eventType) {
        for (auto observer : nodeObservers) {
            observer->onNodeEvent(eventType);
        }
    }
};