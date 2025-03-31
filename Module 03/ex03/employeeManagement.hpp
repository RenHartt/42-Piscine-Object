#pragma once

#include "employee.hpp"
#include <set>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

std::string demangle(const char* mangled_name) {
    int status = 0;
    char* demangled = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    std::string result = (status == 0 && demangled != NULL) ? demangled : mangled_name;
    free(demangled);
    return result;
}

class EmployeeManager {
private:
    std::set<Employee*> employees;
public:
    void addEmployee(Employee* employee) {
        employees.insert(employee);
    }
    void removeEmployee(Employee* employee) {
        if (employees.erase(employee)) delete employee; 
    }
    void executeWorkday() {
        for (const auto& employee : employees) {
            employee->executeWorkday();
        }
    }
    void calculatePayroll() {
        std::cout << "Payroll for last month:\n";
        for (const auto& employee : employees) {
            std::cout << "Employee at " << demangle(typeid(*employee).name())
            << " - Salary: " << employee->calculateSalary() << "€\n";
        }
    }
};