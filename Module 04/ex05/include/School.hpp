#pragma once

#include <string>
#include <set>

#include "List.hpp"
#include "Person.hpp"
#include "Room.hpp"
#include "Course.hpp"

class School {
private:
    StaffList* _staffList;
    StudentList* _studentList;
    CourseList* _courseList;
    RoomList* _roomList;
    Headmaster *_headmaster;
    Secretary *_secretary;
    HeadmasterOffice *_headmasterOffice;
    SecretarialOffice *_secretarialOffice;
    StaffRestRoom *_staffRestRoom;
    Courtyard *_courtyard;

    std::size_t _professorCount = 1;
    std::size_t _studentCount = 1;
public:
    School() {
        _staffList = &StaffList::getInstance();
        _studentList = &StudentList::getInstance();
        _courseList = &CourseList::getInstance();
        _roomList = &RoomList::getInstance();
        _headmaster = &Headmaster::getInstance();
        _secretary = &Secretary::getInstance();
        _headmasterOffice = &HeadmasterOffice::getInstance();
        _secretarialOffice = &SecretarialOffice::getInstance();
        _staffRestRoom = &StaffRestRoom::getInstance();
        _courtyard = &Courtyard::getInstance();
    }

    Headmaster* getHeadmaster() const { return _headmaster; }
    Secretary* getSecretary() const { return _secretary; }
    Course* getCourse(std::string p_name) const { return _courseList->getFromList(p_name); }
    std::set<Student*> getStudents() const { return _studentList->getList(); }
    std::set<Professor*> getProfessors() const { return _staffList->getProfessors(); }

    void recruteProfessor() {
        std::string name = "Professor" + std::to_string(_professorCount++);
        Professor* professor = new Professor(name);
        _headmaster->attach(professor);
        std::cout << "[School] Recruited professor " << name << std::endl;
    }

    void recruteStudent() {
        std::string name = "Student" + std::to_string(_studentCount++);
        Student* student = new Student(name);
        _headmaster->attach(student);
        std::cout << "[School] Recruited student " << name << std::endl;
    }
 
    void runDayRoutine() {
        std::cout << "[School] Running day routine..." << std::endl;
        _headmaster->enterRoom(_headmasterOffice);
        _secretary->enterRoom(_secretarialOffice);

        launchClasses();
        
        requestRingBell();
        requestRingBell();

        requestRingBell();
        requestRingBell();

        requestRingBell();
        requestRingBell();

        _headmaster->finishYourCourse();
        
        graduationCeremony();

        _headmaster->exitRoom();
        _secretary->exitRoom();
        std::cout << "[School] Day routine finished." << std::endl;
    }
    void launchClasses() { _headmaster->attendYourCourse(); }
    void requestRingBell() { _headmaster->notify(Event::RingBell); }
    void graduationCeremony() {
        std::cout << "[School] Graduation ceremony!" << std::endl;
        for (const auto& student : _studentList->getList()) {
            for (const auto& course : student->getSubscribedCourses()) {
                if (course.second <= 0) {
                    std::cout << "[School] " << student->getName() << " graduated from " << course.first->getName() << std::endl;
                }
            }
        }
    }
};