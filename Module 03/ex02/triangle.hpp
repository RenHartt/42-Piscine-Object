#pragma once

#include <cmath>
#include "shape.hpp"

class Triangle: public Shape {
    private:
        double a, b, c;
    public:
        Triangle(double a, double b, double c): a(a), b(b), c(c) {}
        
        double getArea() const override { 
            double s = (a + b + c) / 2;    
            return sqrt(s * (s - a) * (s - b) * (s - c));
        }
        double getPerimeter() const override { return a + b + c; }
        std::string getType() const override { return "Triangle"; }
        std::set<double> getDimensions() const override { return {a, b, c}; }
        
        void print(std::ostream& os) const override {
            std::set<double> dimensions = getDimensions();
            os << "Triangle - Sides: " << dimensions[0] << ", " << dimensions[1] << ", " << dimensions[2];
        }        
};

std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
    triangle.print(os);
    return os;
}