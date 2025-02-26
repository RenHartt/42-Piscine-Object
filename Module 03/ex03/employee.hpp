#pragma once

class Employee {
    protected:
        int hourlyValue;
    public:
        Employee(int hourlyValue): hourlyValue(hourlyValue) {}
        virtual int executeWorkday() = 0;
        virtual int calculateSalary() const = 0;
        virtual ~Employee() {}
};

class TimeOffTrackable {
    public:
        virtual void logTimeOff(int hours) = 0;
        virtual ~TimeOffTrackable() {}
};

class SchoolTrackable {
    public:
        virtual void logSchoolHours(int hours) = 0;
        virtual ~SchoolTrackable() {}
};