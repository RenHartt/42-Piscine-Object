#pragma once

#include <set>
#include <iostream>

struct set2 {
    set2(): X(0), Y(0) {}
    set2(float X, float Y): X(X), Y(Y) {}

    float X, Y;
};

class Graph {
    public:
        Graph(): size({0, 0}), points(0) {}
        Graph(const set2& size): size(size), points(0) {}
        Graph(const std::set<set2>& points): size({0, 0}), points(points) {}
        Graph(const set2& size, const std::set<set2>& points): size(size), points(points) {}

        const set2& getSize(void) const { return size; }
        const std::set<set2>& getPoints(void) const { return points; }

        void addPoint(const set2& point) { points.push_back(point); }

    private:
        set2 size;
        std::set<set2> points;
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);