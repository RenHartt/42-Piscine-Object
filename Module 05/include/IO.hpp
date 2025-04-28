#pragma once

#include <ostream>
#include "Time.hpp"
#include "Train.hpp"

std::ostream& operator<<(std::ostream& os, const Time& time);
std::ostream& operator<<(std::ostream& os, TrainStateType state);