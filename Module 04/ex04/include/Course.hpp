#pragma once

#include <string>
#include <set>

#include "List.hpp"

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
    Course(std::string p_name, Professor* _responsable = nullptr, int p_numberOfClassToGraduate = 5, int p_maximumNumberOfStudent = 20):
        _name(p_name), 
        _responsable(_responsable),
        _numberOfClassToGraduate(p_numberOfClassToGraduate), 
        _maximumNumberOfStudent(p_maximumNumberOfStudent) {
        CourseList::getInstance().addToList(this);
    }
    ~Course() {}

    const std::string& getName() const { return _name; }
    const Professor* getProfessor() const { return _responsable; }
    const std::set<Student*>& getStudents() const { return _students; }
    std::size_t getNumberOfClassToGraduate() const { return _numberOfClassToGraduate; }
    std::size_t getMaximumNumberOfStudent() const { return _maximumNumberOfStudent; }

    void assign(Professor* p_professor) { _responsable = p_professor; }
    void subscribe(Student* p_student) { _students.insert(p_student); }
    void unsubscribe(Student* p_student) { _students.erase(p_student); }
};
