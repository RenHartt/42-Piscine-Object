#pragma once

#include <set>
#include <memory>
#include <mutex>
#include <iostream>
#include <vector>

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

    const std::set<T*>& getList() const {
        return list;
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

class RoomIDGenerator {
private:
    long long _nextId;
    std::vector<long long> _freeIDs;
    std::mutex mtx;

public:
    RoomIDGenerator() : _nextId(0) {}

    long long generateID() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!_freeIDs.empty()) {
            long long id = _freeIDs.back();
            _freeIDs.pop_back();
            return id;
        }
        return _nextId++;
    }

    void releaseID(long long id) {
        std::lock_guard<std::mutex> lock(mtx);
        _freeIDs.push_back(id);
    }
};

class RoomList : public List<Room>, public Singleton<RoomList> {
private:
    RoomIDGenerator _idGenerator;
protected:
    void printItem(Room* item) override;
public:
    RoomList() : _idGenerator() {}
    
    long long generateID() {
        return _idGenerator.generateID();
    }
    
    void releaseID(long long id) {
        _idGenerator.releaseID(id);
    }
};  