#pragma once

#include "employee.hpp"

class TempWorker: public Employee {
    private:
        int hoursWorked = 0;
    public:
        int executeWorkday() override { 
            hoursWorked += 7; 
            return 7;
        }
        int calculateSalary() const override {
            return hoursWorked * hourlyValue;
        }
        TempWorker(int hourlyValue): Employee(hourlyValue) {}
};

class Apprentice: public Employee, public TimeOffTrackable, public SchoolTrackable {
    private:
        int hoursNotWorked = 0;
        int schoolHours = 0;
    public:
        void logTimeOff(int hours) override {
            hoursNotWorked += hours;
        }
        void logSchoolHours(int hours) override {
            schoolHours += hours;
        }
        int executeWorkday() override {
            if (schoolHours > 0) {
                schoolHours -= 7;
                return 7;
            }
            if (hoursNotWorked > 0) {
                hoursNotWorked -= 7;
                return 0;
            }
            return 7;
        }
        int calculateSalary() const override {
            return ((20 * 7 - hoursNotWorked - schoolHours) * hourlyValue) + (schoolHours * (hourlyValue / 2));
        }
        Apprentice(int hourlyValue): Employee(hourlyValue) {}
};