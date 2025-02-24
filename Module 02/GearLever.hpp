#pragma once

#include <array>
#include "Gear.hpp"
#include "Singleton.hpp"

class GearLever : public Singleton<GearLever> {
    private:
        std::array<Gear, 6> gears;
        int level;
        friend class Singleton<GearLever>;
        GearLever() : level(0) {}
    public:
        using Singleton<GearLever>::getInstance;
        void change();
        Gear* activeGear();
};
