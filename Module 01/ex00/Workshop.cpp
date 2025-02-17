#include "Workshop.hpp"

void Workshop::deleteWorker(Worker& worker) {
    this->workers.erase(&worker);
    LOG_VERBOSE("* Worker has leave Workshop *");
}

void Workshop::executeWorkDay() {
    LOG_VERBOSE("* Workshop launch workday *");
    for (std::set<Worker*>::iterator it = workers.begin(); it != workers.end(); it++) {
        (*it)->work();
    }
}

void Workshop::addWorker(Worker& worker) {
    this->workers.insert(&worker);
}

void Workshop::reviewApplication(Worker& worker) {
    addWorker(worker);
    LOG_VERBOSE("Worker has been accepted into the Workshop.");
}