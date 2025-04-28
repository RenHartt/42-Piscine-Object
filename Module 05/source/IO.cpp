#include "IO.hpp"

std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << "[" << (time.hours.count() < 10 ? "0" : "") << time.hours.count() << ":"
       << (time.minutes.count() < 10 ? "0" : "") << time.minutes.count() << ":"
       << (time.seconds.count() < 10 ? "0" : "") << time.seconds.count() << "]";
    return os;
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