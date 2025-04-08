#pragma once

#include <string>
#include <set>

class Professor;
class Student;
class Classroom;

class Course
{
private:
    std::string _name;
    Classroom* _classroom = nullptr;
    Professor* _responsable = nullptr;
    std::set<Student*> _students;
    int _nbrGraduate;
    int _maxStudent;

public:
    Course(std::string p_name, int p_maxStudent, int p_nbrGraduate): _name(p_name), _maxStudent(p_maxStudent), _nbrGraduate(p_nbrGraduate) {}
    ~Course() {}

    const std::string& getName() const { return _name; }
    
    Professor* getProfessor() const { return _responsable; }
    void assign(Professor* p_professor) { _responsable = p_professor; }
    
    const std::set<Student*>& getStudents() const { return _students; }
    void subscribe(Student* p_student) { _students.insert(p_student); }
    void unsubscribe(Student* p_student) { _students.erase(p_student); }
    
    Classroom* getClassroom() const { return _classroom; }
    void setClassroom(Classroom* p_classroom) { _classroom = p_classroom; }    
    
    int getNumberOfClassToGraduate() const { return _nbrGraduate; }
    void setNumberOfClassToGraduate(int p_number) { _nbrGraduate = p_number; }
    
    int getMaximumNumberOfStudent() const { return _maxStudent; }
    void setMaximumNumberOfStudent(int p_number) { _maxStudent = p_number; }
};
