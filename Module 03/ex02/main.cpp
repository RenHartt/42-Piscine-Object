#include <iostream>
#include <set>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

int main() {
    std::set<Shape*> shapes;

    Rectangle rectangle(5, 10);
    Triangle triangle(3, 4, 5);
    Circle circle(4);

    shapes.push_back(&rectangle);
    shapes.push_back(&circle);
    shapes.push_back(&triangle);

    std::cout << std::endl;
    for (const auto& shape : shapes) {
        std::cout << *shape << std::endl;
        std::cout << "Area: " << shape->getArea() << std::endl;
        std::cout << "Perimeter: " << shape->getPerimeter() << std::endl;
        std::cout << std::endl;
    }

    return 0;
}
