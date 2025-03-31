#pragma once

#include "shape.hpp"

class Rectangle: public Shape {
    private:
        double width, height;
    public:
        Rectangle(double width, double height): width(width), height(height) {}

        double getArea() const override { return width * height; }
        double getPerimeter() const override { return 2 * width + 2 * height; }
        std::vector<double> getDimensions() const override { return {width, height}; }
        
        void print(std::ostream& os) const override {
            std::vector<double> dimensions = getDimensions();
            os << "Rectangle - Width: " << dimensions[0] << ", Height: " << dimensions[1];
        }        
};