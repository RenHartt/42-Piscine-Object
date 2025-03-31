#pragma once

#include "employee.hpp"

class ContractEmployee: public Employee, public TimeOffTrackable {
public:
    ContractEmployee(int hourlyValue): Employee(hourlyValue) {}
     
    int executeWorkday() override {
        std::cout << "ContractEmployee working for 7 hours" << std::endl;
        hoursWorked += 7;
        return 7;
    }

    int calculateSalary() const override {
        return (20 * 7 - hoursNotWorked) * hourlyValue;
    }
};