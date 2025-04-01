#pragma once

#include <string>
#include <set>

class Professor;
class Student;

class Course
{
private:
    std::string _name;
    Professor* _responsable = nullptr;
    std::set<Student*> _students;
    int _numberOfClassToGraduate;
    int _maximumNumberOfStudent;

public:
    Course(std::string p_name) : _name(p_name) {}
    ~Course() {}

    const std::string& getName() const { return _name; }
    const Professor* getProfessor() const { return _responsable; }
    const std::set<Student*>& getStudents() const { return _students; }

    void assign(Professor* p_professor);
    void subscribe(Student* p_student);
};
