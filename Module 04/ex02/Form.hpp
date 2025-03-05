#pragma once

#include <iostream>

class Headmaster;

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
        void setFilled(bool state) { _isFilled = state; }
        void signForm() { _signed = true; }
        
    public:
        Form(FormType p_formType) : _formType(p_formType), _signed(false), _isFilled(false) {}
        virtual ~Form() {}

        virtual void execute() = 0;

        bool isSigned() const { return _signed; }
        bool isFilled() const { return _isFilled; }
        FormType getFormType() { return _formType; }
};

class CourseFinishedForm : public Form {
    private:
        std::string _studentName;
        std::string _courseName;
    
    public:    
        CourseFinishedForm() : Form(FormType::CourseFinished) {}
        
        void fillForm(const std::string& studentName, const std::string& courseName) {
            _studentName = studentName;
            _courseName = courseName;
            setFilled(true);
            std::cout << "Course Finished Form filled for student: " << _studentName 
                      << ", course: " << _courseName << std::endl;
        }
        
        void execute() override {
            if (isSigned() == true) {
                std::cout << "Processing Course Finished Form for " << _studentName 
                << " in course: " << _courseName << std::endl;
            }
        }
};

class NeedMoreClassRoomForm : public Form {
    private:
        int _roomCount;
        std::string _reason;
    
    public:    
        NeedMoreClassRoomForm() : Form(FormType::NeedMoreClassRoom) {}
        
        void fillForm(int roomCount, const std::string& reason) {
            _roomCount = roomCount;
            _reason = reason;
            setFilled(true);
            std::cout << "Need More Classroom Form filled. Rooms requested: " << _roomCount 
                      << ", Reason: " << _reason << std::endl;
        }

        void execute() override {
            if (isSigned() == true) {
                std::cout << "Allocating " << _roomCount << " new classrooms due to: " 
                << _reason << std::endl;
            }
        }
};

class NeedCourseCreationForm : public Form {
    private:
        std::string _courseName;
        std::string _professor;
    
    public:    
        NeedCourseCreationForm() : Form(FormType::NeedCourseCreation) {}
        
        void fillForm(const std::string& courseName, const std::string& professor) {
            _courseName = courseName;
            _professor = professor;
            setFilled(true);
            std::cout << "Need Course Creation Form filled. Course: " << _courseName 
                      << ", Professor: " << _professor << std::endl;
        }

        void execute() override {
            if (isSigned() == true) {
                std::cout << "New course created: " << _courseName
                << " by professor " << _professor << "." << std::endl;
            }
        }
};

class SubscriptionToCourseForm : public Form {
    private:
        std::string _studentName;
        std::string _courseName;
    
    public:    
        SubscriptionToCourseForm() : Form(FormType::SubscriptionToCourse) {}
        
        void fillForm(const std::string& studentName, const std::string& courseName) {
            _studentName = studentName;
            _courseName = courseName;
            setFilled(true);
            std::cout << "Subscription to Course Form filled. Student: " << _studentName 
                      << ", Course: " << _courseName << std::endl;
        }

        void execute() override {
            if (isSigned() == true) {
                std::cout << _studentName << " has been successfully enrolled in "
                << _courseName << "." << std::endl;
            }
        }
};    