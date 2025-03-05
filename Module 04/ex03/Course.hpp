#pragma once

#include <memory>
#include <set>
#include <string>

class Course
{
    private:
        std::string _name;
        std::shared_ptr<Professor> _responsable;
        std::set<std::shared_ptr<Student>> _students;
        int _numberOfClassToGraduate;
        int _maximumNumberOfStudent;

    public:
        Course(std::string p_name): _name(p_name), _responsable(nullptr) {}
        
        std::string getName() const { return _name; }

        void assign(std::shared_ptr<Professor> p_professor) { _responsable = p_professor; }
        void subscribe(std::shared_ptr<Student> p_student) { _students.insert(p_student); }
};