#include <iostream>
#include <vector>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main() {
    std::vector<Shape*> shapes = {
        new Rectangle(5, 10),
        new Circle(4),
        new Triangle(3, 4, 5)
    };
    
    for (const auto& shape : shapes) {
        std::cout << *shape << std::endl;
        std::cout << "Area: " << shape->getArea() << std::endl;
        std::cout << "Perimeter: " << shape->getPerimeter() << std::endl;
        std::cout << std::endl;
    }

    for (const auto& shape : shapes) {
        delete shape;
    }

    return 0;
}
