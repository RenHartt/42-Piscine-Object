#pragma once

#include <set>
#include "Logger.hpp"

class Worker;

class Workshop {
    public:
        Workshop();

        void reviewApplication(const Worker& worker);
    
    private:
        std::set<Worker*> workers;
};