#pragma once

#include <memory>
#include <set>
#include <string>

class Professor;
class Student;

class Course
{
    private:
        std::string _name;
        std::shared_ptr<Professor> _responsable;
        std::set<std::shared_ptr<Student>> _students;
        int _numberOfClassToGraduate;
        int _maximumNumberOfStudent;

    public:
        Course(std::string p_name);
        
        std::string getName() const;

        void assign(std::shared_ptr<Professor> p_professor);
        void subscribe(std::shared_ptr<Student> p_student);
};