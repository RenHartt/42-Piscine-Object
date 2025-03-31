#pragma once

class Employee {
protected:
    int hourlyValue = 0;
    int hoursWorked = 0;
public:
    Employee(int hourlyValue): hourlyValue(hourlyValue) {}
    virtual ~Employee() {}

    virtual int executeWorkday() = 0;
    virtual int calculateSalary() const = 0;
};

class WorkHoursNeededTrackable {
protected:
    int hoursNeeded = 140;
public:
    virtual ~WorkHoursNeededTrackable() {}
    
    virtual void logHoursNeeded(int hours) {
        hoursNeeded = hours;
    }
};

class TimeOffTrackable {
protected:
    int hoursNotWorked = 0;
public:
    virtual ~TimeOffTrackable() {}
    
    virtual void logTimeOff(int hours) {
        hoursNotWorked += hours;
    }
};

class SchoolTrackable {
protected:
    int schoolHours = 0;  
public:
    virtual ~SchoolTrackable() {}
    
    virtual void logSchoolHours(int hours) {
        schoolHours += hours;
    }
};