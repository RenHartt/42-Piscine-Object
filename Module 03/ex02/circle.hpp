#pragma once

#include "shape.hpp"
#include <cmath>

#define PI 3.14159265358979323846

class Circle: public Shape {
    private:
        double radius;
    public:
        Circle(double radius): radius(radius) {}

        double getArea() const override { return radius * radius * PI; }
        double getPerimeter() const override { return (radius + radius) * PI; }
        std::string getType() const override { return "Circle"; }
        std::vector<double> getDimensions() const override { return {radius}; }

        void print(std::ostream& os) const override {
            std::vector<double> dimensions = getDimensions();
            os << "Circle - Radius: " << dimensions[0];
        }        
};

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    circle.print(os);
    return os;
}