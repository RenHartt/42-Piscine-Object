#pragma once

#include "LinkablePart.hpp"
#include <array>
#include "Brake.hpp"

class BrakeController : public LinkablePart {
    private:
        std::array<Brake, 4> brakes;
    public:
        BrakeController() = default;
        void execute(float p_pression) override;
};