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

    if (getDistanceOnSegment() >= rail->getLength() - 0.001f) {
        state.setStateType(TrainStateType::Stop);
        setSpeed(0.0f);
        log();
        setCountdown(getStopDuration());
        setDistanceOnSegment(0.0f);
        setCurrentPart(getNextPart());
    } else {
        log();
    }
}

void Train::travelOnNode(const Time& time) {
    setCountdown(getCountdown() - time);
    if (getCountdown().toFloat() <= 0) {
        requestRoute();
        setCurrentPart(getNextPart());
        setCountdown(getStopDuration());
        setDistanceOnSegment(0.0f);
        setSpeed(0.0f);
    } else {
        setCountdown(Time(0, 0, 1));
    }
}

void Train::travel(const Time& time) {
    if (dynamic_cast<Rail*>(getCurrentPart())) {
        travelOnRail(time);
    } else if (dynamic_cast<Node*>(getCurrentPart())) {
        travelOnNode(time);
    }
}

void Train::update(const Time& time) {
    const Time& globalTime = Simulation::getInstance().getGlobalTime();
    if (globalTime.toFloat() < getDepartureTime().toFloat()) return;
    if (getRoute().empty()) {
        requestRoute();
        if (getRoute().empty()) return;
        setCurrentPart(getNextPart());
    } else {
        travel(time);
    }
}

void Train::log() {
    if (Rail* rail = dynamic_cast<Rail*>(getCurrentPart())) {
        std::ostringstream oss;
        Time globalTime = Simulation::getInstance().getGlobalTime();
        std::string name = "[" + getName() + "]";
        std::string departure = "[" + rail->getDeparture()->getName() + "]";
        std::string arrival = "[" + rail->getArrival()->getName() + "]";
        std::string distance = "[" + std::to_string((rail->getLength() - getDistanceOnSegment()) / 1000) + "]";
        TrainStateType status = getStateType();
        std::string position;
        for (int i = 0; i <= (int)rail->getLength() / 1000; ++i) {
            (i == (int)getDistanceOnSegment() / 1000) ? position += "[x]" : position += "[ ]";
        }
        oss << globalTime << " - " << name << " - " << departure << arrival << " - "
            << distance << " - " << status << " - " << position;
        logger.write(oss.str());
    } else {
        throw std::runtime_error("Train is not on a segment");
    }
   
}

std::ostream& operator<<(std::ostream& os, TrainStateType state) {
    switch (state) {
        case TrainStateType::Accelerate: os << "[Speed up]"; break;
        case TrainStateType::ConstantSpeed: os << "[Maintain]"; break;
        case TrainStateType::Decelerate: os << "[ Braking]"; break;
        case TrainStateType::Stop: os << "[ Stopped]"; break;
    }
    return os;
}