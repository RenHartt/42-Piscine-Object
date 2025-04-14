#include <iostream>

#include "School.hpp"

#define PROFESSOR_COUNT 100
#define STUDENT_COUNT 11000
#define DAY_COUNT 150

int main() {
    School school;

    for (int i = 0; i < PROFESSOR_COUNT; ++i) {
        school.recruteProfessor();
    }
    for (int i = 0; i < STUDENT_COUNT; ++i) {
        school.recruteStudent();
    }
    for (int i = 0; i < DAY_COUNT; ++i) {
        std::cout << std::endl;
        std::cout << "==================== Day " << i + 1 << " ====================" << std::endl;
        school.runDayRoutine();
    }

    return 0;
}
