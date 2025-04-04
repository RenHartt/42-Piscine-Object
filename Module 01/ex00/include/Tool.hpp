#pragma once

#include "Logger.hpp"

class Tool {
    public:
        Tool(int numberOfUses): numberOfUses(numberOfUses) { LOG_VERBOSE("* Tool created *"); }
        virtual ~Tool() {}
        int getNumberOfUses() const;

        virtual void use() = 0;
    
    protected :
        void decreaseDurability();
    
    private:
        int numberOfUses;
};

class Hammer : public Tool {
    public:
        Hammer(int numberOfUses = 0): Tool(numberOfUses) { LOG_VERBOSE("* Hammer created *"); }

        void use();
};

class Shovel : public Tool {
    public:
        Shovel(int numberOfUses = 0): Tool(numberOfUses) { LOG_VERBOSE("* Shovel created *"); }

        void use();
};