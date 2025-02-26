#pragma once

#include "employee.hpp"

class ContractEmployee: public Employee, public TimeOffTrackable {
    private:
        int hoursNotWorked = 0;
    public:
    void logTimeOff(int hours) override {
        hoursNotWorked += hours;
    }
    int executeWorkday() override {
        if (hoursNotWorked > 0) {
            hoursNotWorked -= 7;
            return 0;
        }
        return 7;
    }
    int calculateSalary() const override {
        return (20 * 7 - hoursNotWorked) * hourlyValue;
    }
    ContractEmployee(int hourlyValue): Employee(hourlyValue) {}
};