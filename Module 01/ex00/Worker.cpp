#include "Worker.hpp"

void Worker::addTool(Tool* tool) {
    if (tool) {
        this->tools.insert(tool);
        LOG_VERBOSE("* Worker take a tool *");
    } 
}

void Worker::removeTool(Tool* tool) {
    if (tool) {
        this->tools.erase(tool);
        LOG_VERBOSE("* Worker drop a tool *");
    }
}

void Worker::giveTool(Worker& worker, Tool* tool) {
    if (!tool || &worker == this) return;

    if (this->tools.find(tool) != this->tools.end()) {
        this->removeTool(tool);
        worker.addTool(tool);
        LOG_VERBOSE("* Tool has been transferred to another worker! *");
    } else {
        LOG_VERBOSE("Error: Worker does not own this tool!");
    }
}

void Worker::joinWorkShop(Workshop& workshop) {
    workshop.reviewApplication(*this);
    LOG_VERBOSE("* Worker join workshop *");
}

void Worker::leaveWorkShop(Workshop& workshop) {
    workshop.deleteWorker(*this);
    this->workshops.erase(&workshop);
    LOG_VERBOSE("* Worker leave workshop *");
}

void Worker::work() {
    LOG_VERBOSE("* Worker doing work *");
}