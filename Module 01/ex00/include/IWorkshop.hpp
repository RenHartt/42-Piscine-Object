#pragma once

#include <typeinfo>

class Worker;

class IWorkshop {
    public:
        virtual ~IWorkshop() {}
        virtual void reviewApplication(Worker& worker) = 0;
        virtual void deleteWorker(Worker& worker) = 0;
        virtual const std::type_info& getRequiredToolType() const = 0;
};