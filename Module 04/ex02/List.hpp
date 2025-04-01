#pragma once

#include <set>
#include <memory>
#include <mutex>
#include <iostream>

#include "Singleton.hpp"

class Student;
class Staff;
class Course;
class Room;

template <typename T>
class List {
protected:
    std::set<T*> list;
    std::mutex mtx;

    virtual void printItem(T* item) = 0;

public:
    virtual ~List() {
        for (const auto& item : list) {
            delete item;
        }
        list.clear();
    }
    
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
protected:
    void printItem(Student* item) override;
};

class StaffList : public List<Staff>, public Singleton<StaffList> {
protected:
    void printItem(Staff* item) override;
};

class CourseList : public List<Course>, public Singleton<CourseList> {
protected:
    void printItem(Course* item) override;
};

class RoomList : public List<Room>, public Singleton<RoomList> {
protected:
    void printItem(Room* item) override;
};