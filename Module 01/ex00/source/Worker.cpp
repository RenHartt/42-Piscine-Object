#include "Worker.hpp"
#include <iterator>
#include <typeinfo>

bool Worker::hasTool(const std::type_info& type) const {
    for (std::set<Tool*>::iterator it = tools.begin(); it != tools.end(); ++it) {
        Tool* tool = *it;
        if (tool && typeid(*tool) == type) {
            return true;
        }
    }
    return false;
}

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

void Worker::joinWorkShop(IWorkshop& workshop) {  
    workshops.insert(&workshop);
    workshop.reviewApplication(*this);
}

void Worker::leaveWorkShop(IWorkshop& workshop) {  
    workshops.erase(&workshop);
    LOG_VERBOSE("* Worker left the Workshop *");
}