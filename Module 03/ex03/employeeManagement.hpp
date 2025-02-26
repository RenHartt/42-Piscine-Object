#pragma once

#include "employee.hpp"
#include <set>
#include <iostream>

class EmployeeManager {
    private:
        std::set<Employee*> employees;
        int totalWorkedHours = 0;
    public:
        void addEmployee(Employee* employee) {
            employees.insert(employee);
        }
        void removeEmployee(Employee* employee) {
            if (employees.erase(employee)) delete employee; 
        }
        void executeWorkday() {
            for (const auto& employee : employees) {
                totalWorkedHours += employee->executeWorkday();
            }
        }
        void calculatePayroll() {
            std::cout << "Payroll for last month:\n";
            for (const auto& employee : employees) {
                std::cout << "Employee at " << employee 
                          << " - Salary: " << employee->calculateSalary() 
                          << "€\n";
            }
        }
};