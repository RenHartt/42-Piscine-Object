#pragma once

#include <cstdlib>
#include <random>

#include "Event.hpp"

class RandomEvent : public RailEventSource, public NodeEventSource {
private:
    static std::mt19937& rng() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

    static bool tirage(float probability) {
        std::uniform_real_distribution<float> dist(0.0f, 100.0f);
        return dist(rng()) < probability;
    }

    void randomRailEvent(float probability) {
        for (const auto& observer : railObservers) {
            RailEventType event = tirage(probability)
                ? RailEventType::RailClose 
                : RailEventType::RailOpen;
            observer->onRailEvent(event);
        }
    }

    void randomNodeEvent(float probability) {
        for (const auto& observer : nodeObservers) {
            NodeEventType event = tirage(probability)
                ? NodeEventType::NodeClose 
                : NodeEventType::NodeOpen;
            observer->onNodeEvent(event);
        }
    }
public:
    void randomEvent(float probability) {
        randomRailEvent(probability);
        randomNodeEvent(probability);
    }
};