#pragma once

#include <string>
#include <set>

class Shape {
    public:
        virtual double getArea() const = 0;
        virtual double getPerimeter() const = 0;
        virtual std::string getType() const = 0;
        virtual std::set<double> getDimensions() const = 0;
    
        virtual void print(std::ostream& os) const = 0;
        virtual ~Shape() {}
    };
    
std::ostream& operator<<(std::ostream& os, const Shape& shape) {
    shape.print(os);
    return os;
}