#include "Simulation.hpp"
#include "Observer.hpp"
#include "Train.hpp"
#include "Rail.hpp"
#include "Node.hpp"
#include "Utils.hpp"
#include "Event.hpp"

void Train::requestRoute() {
    setRoute(Simulation::getInstance().calculateRoute(*this));
}

LinkablePart* Train::getNextPart() {
    std::list<LinkablePart*> route = getRoute();
    std::list<LinkablePart*>::iterator it = std::find(route.begin(), route.end(), getCurrentPart());
    if (it != route.end() && ++it != route.end()) {
        return *it;
    }
    return nullptr;
}

void Train::travelOnRail(const Time& time) {
    const Rail* rail = dynamic_cast<const Rail*>(state.getCurrentPart());
   
    float currentSpeed = getSpeed();
    float breakingDistance = calculateBrakingDistance();
    float remainingDistance = rail->getLength() - getDistanceOnSegment();

    if (remainingDistance > breakingDistance) {
        if (currentSpeed < rail->getSpeedLimit()) {
            state.setStateType(TrainStateType::Accelerate);
            float newSpeed = currentSpeed + getAccelerationCoefficient() * time.toFloat();
            if (newSpeed > rail->getSpeedLimit()) newSpeed = rail->getSpeedLimit();
            setSpeed(newSpeed);
        } else {
            state.setStateType(TrainStateType::ConstantSpeed);
            setSpeed(rail->getSpeedLimit());
        }
    } else  {
        state.setStateType(TrainStateType::Decelerate);
        setSpeed(currentSpeed - getBrakingCoefficient() * time.toFloat());
    }
    float distancetravelled = getDistanceOnSegment() + currentSpeed * time.toFloat();
    if (distancetravelled > rail->getLength()) { distancetravelled = rail->getLength(); }
    setDistanceOnSegment(distancetravelled);
    
    std::cout << "Train " << getName() << " is on rail segment " << rail->getId() << " with distance: " << getDistanceOnSegment() / 1000 << " and speed: " << getSpeed() / (5./18.) << std::endl;
    
    if (getDistanceOnSegment() >= rail->getLength()) {
        setCountdown(getStopDuration());
        setDistanceOnSegment(0.0f);
        setSpeed(0.0f);
        setCurrentPart(getNextPart());
    }
}

void Train::travelOnNode(const Time& time) {
    const Node* node = dynamic_cast<const Node*>(state.getCurrentPart());
    setCountdown(getCountdown() - time);
    
    std::cout << "Train " << getName() << " is at node " << node->getName() << " with countdown: " << getCountdown().toString() << std::endl;
    
    if (getCountdown().toFloat() <= 0) {
        setCountdown(getStopDuration());
        setCurrentPart(getNextPart());
        requestRoute();
    }
}

void Train::travel(const Time& time) {
    if (getCurrentPart() == nullptr) {
        throw std::runtime_error("Train is not on a segment");
    }

    const Rail* rail = dynamic_cast<const Rail*>(getCurrentPart());
    if (rail != nullptr) {
        travelOnRail(time);
    } else {
        travelOnNode(time);
    }
}

void Train::update(const Time& time) {
    if (getCurrentPart() == nullptr) {
        return;
    }
    travel(time);
}