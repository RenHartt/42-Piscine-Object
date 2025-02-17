#pragma once

#include <set>
#include "Logger.hpp"
#include "Worker.hpp"

class Worker;

class Workshop {
    public:
        Workshop() { LOG_VERBOSE("* Workshop created *"); }

        void deleteWorker(Worker& worker);

        void executeWorkDay();

    private:
        std::set<Worker*> workers;

        void addWorker(Worker& worker);
        void reviewApplication(Worker& worker);

        friend class Worker;
};
