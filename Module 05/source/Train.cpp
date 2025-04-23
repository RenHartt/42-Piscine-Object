#include "Simulation.hpp"
#include "Observer.hpp"
#include "Train.hpp"
#include "Rail.hpp"
#include "Node.hpp"
#include "Utils.hpp"
#include "Event.hpp"

void Train::requestRoute() {
    setRoute(Simulation::getInstance().calculateRoute(this));
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
    for (int sec = 0; sec < (int)time.toFloat(); ++sec) {
        float currentSpeed = getSpeed();
        float timeStep = time.toFloat();
        float nextSpeed = currentSpeed + getAccelerationCoefficient() * timeStep;

        float nextBrakingDistance = (nextSpeed * nextSpeed) / (2 * getBrakingCoefficient());
        float remainingDistance = rail->getLength() - getDistanceOnSegment() - (nextSpeed * timeStep);

        if (remainingDistance <= nextBrakingDistance) {
            state.setStateType(TrainStateType::Decelerate);
            float newSpeed = currentSpeed - getBrakingCoefficient() * timeStep;
            if (newSpeed < 3.0f) newSpeed = 3.0f;
            setSpeed(newSpeed);
        } else if (currentSpeed < rail->getSpeedLimit()) {
            state.setStateType(TrainStateType::Accelerate);
            float newSpeed = currentSpeed + getAccelerationCoefficient() * timeStep;
            if (newSpeed > rail->getSpeedLimit()) newSpeed = rail->getSpeedLimit();
            setSpeed(newSpeed);
        } else {
            state.setStateType(TrainStateType::ConstantSpeed);
            setSpeed(rail->getSpeedLimit());
        }

        float distancetravelled = getDistanceOnSegment() + getSpeed() * timeStep;
        if (distancetravelled > rail->getLength()) {
            distancetravelled = rail->getLength();
        }
        setDistanceOnSegment(distancetravelled);
    }

    std::cout << "Train " << getName() << " is on rail segment " << rail->getId()
            << " with distance: " << getDistanceOnSegment() / 1000
            << " and speed: " << getSpeed() / (5.0f / 18.0f) << std::endl;

    if (getDistanceOnSegment() >= rail->getLength() - 0.001f) {
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