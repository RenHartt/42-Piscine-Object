#pragma once

#include <set>
#include "Logger.hpp"
#include "IWorkshop.hpp"
#include "Worker.hpp"
#include <typeinfo>

template<typename ToolType>
class Workshop : public IWorkshop {
    public:
        Workshop() { 
            LOG_VERBOSE("* Workshop created for " + std::string(typeid(ToolType).name()) + " *"); 
        }

        const std::type_info& getRequiredToolType() const {
            return typeid(ToolType);
        }

        void reviewApplication(Worker& worker) {
            LOG_VERBOSE("* Workshop received application *");

            if (!worker.GetTool<ToolType>()) {
                LOG_VERBOSE("* Worker rejected: Missing required tool *");
            } else {
                addWorker(worker);
                LOG_VERBOSE("* Worker has been accepted into the Workshop *");
            }
        }

        bool containsWorker(Worker* worker) const {
            return workers.find(worker) != workers.end();
        }

        void deleteWorker(Worker& worker) {
            if (workers.find(&worker) != workers.end()) {
                LOG_VERBOSE("* Worker removed from Workshop *");
                workers.erase(&worker);
                worker.leaveWorkShop(*this);
            }
        }

        void executeWorkDay() {
            LOG_VERBOSE("* Workshop launch workday *");
            for (std::set<Worker*>::iterator it = this->workers.begin(); it != this->workers.end(); ) {
                Worker* worker = *it;
                ++it;

                worker->work<ToolType>();
            }
        }

        std::set<Worker*> workers;
    private:

        void addWorker(Worker& worker) { 
            workers.insert(&worker); 
            LOG_VERBOSE("* Worker added to the Workshop *");
        }
};
