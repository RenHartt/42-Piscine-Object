#pragma once

#include "Logger.hpp"

class Tool {
    public:
        Tool(int numberOfUses): numberOfUses(numberOfUses) { LOG_VERBOSE("* Tool created *"); }

        virtual void use() = 0;
    
    protected :
        void decreaseDurability();
    
    private:
        int numberOfUses;
};

class Hammer : public Tool {
    public:
        Hammer(int numberOfUses): Tool(numberOfUses) { LOG_VERBOSE("* Hammer created *"); }

        void use();
};

class Shovel : public Tool {
    public:
        Shovel(int numberOfUses): Tool(numberOfUses) { LOG_VERBOSE("* Shovel created *"); }

        void use();
};