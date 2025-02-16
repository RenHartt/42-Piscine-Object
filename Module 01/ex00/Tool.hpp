#pragma once

#include "Logger.hpp"

class Tool {
    public:
        Tool(int numberOfUses): numberOfUses(numberOfUses) {}

        virtual void use() = 0;
    
    protected :
        void decreaseDurability() {
            if (numberOfUses > 0) {
                numberOfUses--;
            } else {
                LOG_VERBOSE("* The tool has broken *");
            }
        }
    
    private:
        int numberOfUses;
};

class Hammer : public Tool {
    public:
        Hammer(int numberOfUses): Tool(numberOfUses) {}

        void use() { decreaseDurability(); }
};

class Shovel : public Tool {
    public:
        Shovel(int numberOfUses): Tool(numberOfUses) {}

        void use() { decreaseDurability(); }
};