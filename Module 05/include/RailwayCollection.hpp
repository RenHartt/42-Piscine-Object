#pragma once

#include "Singleton.hpp"

#include <unordered_set>
#include <mutex>

class Train;
class Rail;
class Node;

template<typename T>
class Set {
protected:
    std::mutex mtx;
    std::unordered_set<T*> elements;

    virtual void printItem(T* item) const = 0;
public:
    void add(T* element) {
        std::lock_guard<std::mutex> lock(mtx);
        elements.insert(element);
    }

    void remove(T* element) {
        std::lock_guard<std::mutex> lock(mtx);
        elements.erase(element);
    }

    const std::unordered_set<T*>& getElements() {
        return elements;
    }

    bool contains(T* element) {
        std::lock_guard<std::mutex> lock(mtx);
        return elements.find(element) != elements.end();
    }

    void clear() {
        std::lock_guard<std::mutex> lock(mtx);
        elements.clear();
    }

    T* getById(long long id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& element : elements) {
            if (element->getId() == id) {
                return element;
            }
        }
        return nullptr;
    }

    T* getByName(const std::string& name) {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& element : elements) {
            if (element->getName() == name) {
                return element;
            }
        }
        return nullptr;
    }

    void print() {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& element : elements) {
            printItem(element);
        }
    }
};

class TrainCollection : public Set<Train>, public Singleton<TrainCollection> {
public:
    ~TrainCollection();

    void printItem(Train* item) const override;
};

class RailCollection : public Set<Rail>, public Singleton<RailCollection> {
public:
    ~RailCollection();

    void printItem(Rail* item) const override;
};

class NodeCollection : public Set<Node>, public Singleton<NodeCollection> {
public:
    ~NodeCollection();

    void printItem(Node* item) const override;
};