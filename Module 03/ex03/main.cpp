#include <iostream>
#include "employeeManagement.hpp"
#include "hourlyEmployee.hpp"
#include "salariedEmployee.hpp"

int main() {
    EmployeeManager manager;

    // Création des employés avec un taux horaire de 15€
    TempWorker worker(15);
    ContractEmployee contract(20);
    Apprentice apprentice(10);

    // Ajout des employés au manager
    manager.addEmployee(&worker);
    manager.addEmployee(&contract);
    manager.addEmployee(&apprentice);

    // Ajout d'heures spéciales
    contract.logTimeOff(14);  // 2 jours d'absence
    apprentice.logTimeOff(7); // 1 jour d'absence
    apprentice.logSchoolHours(21); // 3 jours d'école

    // Simuler 20 jours de travail
    for (int i = 0; i < 20; i++) {
        manager.executeWorkday();
    }

    std::cout << "\n=== Calcul des paies ===\n";
    manager.calculatePayroll();

    return 0;
}
