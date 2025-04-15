#pragma once

#include <set>
#include <memory>
#include <mutex>
#include <iostream>

#include "Singleton.hpp"

class Professor;
class Student;
class Staff;
class Course;
class Room;
class Classroom;

template <typename T>
class List {
protected:
    std::set<T*> list;
    std::mutex mtx;

    virtual void printItem(T* item) = 0;

public:
    virtual ~List() {}
    
    void addToList(T* toAdd) {
        std::lock_guard<std::mutex> lock(mtx);
        list.insert(toAdd);
    }

    void removeFromList(T* toRemove) {
        std::lock_guard<std::mutex> lock(mtx);
        list.erase(toRemove);
    }

    T* getFromList(const std::string& toGet) {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& item : list) {
            if (item->getName() == toGet) {
                return item;
            }
        }
        return nullptr;
    }

    void printList() {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& item : list) {
            printItem(item);
        }
    }
};

class StudentList : public List<Student>, public Singleton<StudentList> {
public:
    ~StudentList();

    void printItem(Student* item) override;
};

class StaffList : public List<Staff>, public Singleton<StaffList> {
private:
    std::set<Professor*> getProfessors();
public:
    ~StaffList();

    void printItem(Staff* item) override;
};

class CourseList : public List<Course>, public Singleton<CourseList> {
public:
    ~CourseList();

    void printItem(Course* item) override;
};

class RoomList : public List<Room>, public Singleton<RoomList> {
private:
    std::set<Classroom*> getClassrooms();
public:
    ~RoomList();

    void printItem(Room* item) override;
};