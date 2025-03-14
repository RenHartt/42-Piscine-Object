#pragma once

#include "shape.hpp"

class Rectangle: public Shape {
    private:
        double width, height;
    public:
        Rectangle(double width, double height): width(width), height(height) {}

        double getArea() const override { return width * height; }
        double getPerimeter() const override { return 2 * width + 2 * height; }
        std::string getType() const override { return "Rectangle"; }
        std::set<double> getDimensions() const override { return {width, height}; }
        
        void print(std::ostream& os) const override {
            std::set<double> dimensions = getDimensions();
            os << "Rectangle - Width: " << dimensions[0] << ", Height: " << dimensions[1];
        }        
};

std::ostream& operator<<(std::ostream& os, const Rectangle& retangle) {
    retangle.print(os);
    return os;
}