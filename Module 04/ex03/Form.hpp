#pragma once

#include <iostream>
#include <memory>

class Student;
class Course;
class Professor;

enum class FormType {
    CourseFinished,
    NeedMoreClassRoom,
    NeedCourseCreation,
    SubscriptionToCourse
};

class Form {
    private:
        FormType _formType;
        bool _signed;
        bool _isFilled;
        
        friend class Headmaster;
        
    protected:
        void setFilled(bool state);
        void signForm();
        
    public:
        Form(FormType p_formType);
        virtual ~Form();
        
        virtual void execute() = 0;
        
        bool isSigned() const;
        bool isFilled() const;
        FormType getFormType();
};

class CourseFinishedForm : public Form {
    private:
        std::shared_ptr<Student> _student;
        std::shared_ptr<Course> _course;
        
    public:    
        CourseFinishedForm();
        
        void fillForm(std::shared_ptr<Student> student, std::shared_ptr<Course> course);
        void execute() override;
};

class NeedMoreClassRoomForm : public Form {
    private:
        int _roomCount;
        std::string _reason;
        
    public:
        NeedMoreClassRoomForm();
        
        void fillForm(int roomCount, const std::string& reason);
        void execute() override;
};

class NeedCourseCreationForm : public Form {
    private:
        std::shared_ptr<Course> _course;
        std::shared_ptr<Professor> _professor;
        
    public:    
        NeedCourseCreationForm();
        
        void fillForm(std::shared_ptr<Course> course, std::shared_ptr<Professor> professor);
        void execute() override;
};

class SubscriptionToCourseForm : public Form {
    private:
        std::shared_ptr<Student> _student;
        std::shared_ptr<Course> _course;
    
    public:    
        SubscriptionToCourseForm();
            
        void fillForm(std::shared_ptr<Student> student, std::shared_ptr<Course> course);
        void execute() override;
};