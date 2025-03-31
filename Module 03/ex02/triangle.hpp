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
        std::vector<double> getDimensions() const override { return {a, b, c}; }
        
        void print(std::ostream& os) const override {
            std::vector<double> dimensions = getDimensions();
            os << "Triangle - Sides: " << dimensions[0] << ", " << dimensions[1] << ", " << dimensions[2];
        }        
};