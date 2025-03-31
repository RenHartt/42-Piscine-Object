#include <iostream>
#include "employeeManagement.hpp"
#include "hourlyEmployee.hpp"
#include "salariedEmployee.hpp"

int main() {
    EmployeeManager manager;

    TempWorker worker(15);
    ContractEmployee contract(20);
    Apprentice apprentice(10);

    manager.addEmployee(&worker);
    manager.addEmployee(&contract);
    manager.addEmployee(&apprentice);

    worker.logHoursNeeded(26);
    contract.logTimeOff(14);
    apprentice.logTimeOff(14);
    apprentice.logSchoolHours(21);

    for (int i = 1; i <= 20; i++) {
        std::cout << "\n=== Exécution de la journée de travail [" << i << "] ===\n";
        manager.executeWorkday();
    }

    std::cout << "\n=== Calcul des paies ===\n";
    manager.calculatePayroll();

    return 0;
}
