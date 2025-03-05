#include "Course.hpp"

Course::Course(std::string p_name): _name(p_name), _responsable(nullptr) {}

std::string Course::getName() const { return _name; }

void Course::assign(std::shared_ptr<Professor> p_professor) { _responsable = p_professor; }
void Course::subscribe(std::shared_ptr<Student> p_student) { _students.insert(p_student); }