#pragma once

#include <list>
#include <memory>
#include <mutex>

#include "Singleton.hpp"

class Student;
class Staff;
class Course;
class Room;

template <typename T>
class List {
protected:
    std::list<std::shared_ptr<T>> list;
    std::mutex mtx;

public:
    void addToList(std::shared_ptr<T> toAdd) {
        std::lock_guard<std::mutex> lock(mtx);
        list.push_back(toAdd);
    }

    void removeFromList(std::shared_ptr<T> toRemove) {
        std::lock_guard<std::mutex> lock(mtx);
        list.remove(toRemove);
    }

    std::list<std::shared_ptr<T>> getList() const {
        return list;
    }

    virtual ~List() {}
};

class StudentList : public List<Student>, public Singleton<StudentList> {};
class StaffList : public List<Staff>, public Singleton<StaffList> {};
class CourseList : public List<Course>, public Singleton<CourseList> {};
class RoomList : public List<Room>, public Singleton<RoomList> {};
