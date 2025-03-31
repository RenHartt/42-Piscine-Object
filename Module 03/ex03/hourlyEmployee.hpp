#pragma once

#include "employee.hpp"

class TempWorker: public Employee, public WorkHoursNeededTrackable {
public:
    TempWorker(int hourlyValue): Employee(hourlyValue) {}
    
    int executeWorkday() override {
        if (hoursNeeded > 7) {
            std::cout << "TempWorker working for 7 hours" << std::endl;
            hoursWorked += 7;
            hoursNeeded -= 7;
            return 7;
        } else if (hoursNeeded > 0) {
            std::cout << "TempWorker working for " << hoursNeeded << " hours" << std::endl;
            hoursWorked += hoursNeeded;
            int workedHours = hoursNeeded;
            hoursNeeded = 0;
            return workedHours;
        }
        std::cout << "TempWorker has no more hours to work" << std::endl;
        return 0;
    }

    int calculateSalary() const override {
        return hoursWorked * hourlyValue;
    }
};

class Apprentice: public Employee, public TimeOffTrackable, public SchoolTrackable {
public:
    Apprentice(int hourlyValue): Employee(hourlyValue) {}

    int executeWorkday() override {
        std::cout << "Apprentice working for 7 hours" << std::endl;
        hoursWorked += 7;
        return 7;
    }

    int calculateSalary() const override {
        return ((20 * 7 - hoursNotWorked - schoolHours) * hourlyValue) + (schoolHours * (hourlyValue / 2));
    }
};