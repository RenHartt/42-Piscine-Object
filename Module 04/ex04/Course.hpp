#pragma once

#include <string>
#include <set>

#include "List.hpp"

class Professor;
class Student;
class Classroom;

class Course {
private:
    std::string _name;
    Classroom* _classroom = nullptr;
    Professor* _responsable = nullptr;
    std::set<Student*> _students;
    int _requiredClassesToGraduate;
    int _maxStudent;

public:
    Course(const std::string& name, int maxStudent, int requiredClassesToGraduate)
    : _name(name), _maxStudent(maxStudent), _requiredClassesToGraduate(requiredClassesToGraduate) {
        CourseList::getInstance().addToList(this);
    }
    ~Course() {}

    const std::string& getName() const { return _name; }

    Professor* getProfessor() const { return _responsable; }
    void assignProfessor(Professor* professor) { _responsable = professor; }
    void removeProfessor() { _responsable = nullptr; }

    const std::set<Student*>& getStudents() const { return _students; }
    void addStudent(Student* student) { _students.insert(student); }
    void removeStudent(Student* student) { _students.erase(student); }
    bool isStudentSubscribed(Student* student) const { return _students.count(student) > 0; }

    Classroom* getClassroom() const { return _classroom; }
    void assignClassroom(Classroom* classroom) { _classroom = classroom; }
    void removeClassroom() { _classroom = nullptr; }

    int requiredClassesToGraduate() const { return _requiredClassesToGraduate; }
    int maximumStudents() const { return _maxStudent; }
};