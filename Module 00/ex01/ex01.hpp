#pragma once

#include <vector>
#include <iostream>

struct Vector2 {
    Vector2(): X(0), Y(0) {}
    Vector2(float X, float Y): X(X), Y(Y) {}

    float X, Y;
};

class Graph {
    public:
        Graph(): size({0, 0}), points(0) {}
        Graph(const Vector2& size): size(size), points(0) {}
        Graph(const std::vector<Vector2>& points): size({0, 0}), points(points) {}
        Graph(const Vector2& size, const std::vector<Vector2>& points): size(size), points(points) {}

        const Vector2& getSize(void) const { return size; }
        const std::vector<Vector2>& getPoints(void) const { return points; }

        void addPoint(const Vector2& point) { points.push_back(point); }

    private:
        Vector2 size;
        std::vector<Vector2> points;
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);