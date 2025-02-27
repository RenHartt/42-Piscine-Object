#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Person.hpp"

class Course
{
private:
    std::string _name;
    std::unique_ptr<Professor> _responsable;
    std::vector<std::shared_ptr<Student>> _students;
    int _numberOfClassToGraduate;
    int _maximumNumberOfStudent;

public:
    Course(std::string p_name);
    void assign(std::unique_ptr<Professor> p_professor);
    void subscribe(std::shared_ptr<Student> p_student);
};
