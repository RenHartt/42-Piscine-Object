#pragma once

#include <string>
#include <vector>

#include "Utils.hpp"

class Node {
private:
    std::string name;
    Vec2f coordinates;
public:
    Node(const std::string& name, const Vec2f& coordinates) : name(name), coordinates(coordinates) {}

    const std::string& getName() const { return name; }
    const Vec2f& getCoordinates() const { return coordinates; }
    void setName(const std::string& name) { this->name = name; }
    void setCoordinates(const Vec2f& coordinates) { this->coordinates = coordinates; }
    void setCoordinates(float x, float y) { coordinates = Vec2f(x, y); }
    void setCoordinates(const float arr[2]) { coordinates = Vec2f(arr[0], arr[1]); }
};