#include "ex01.hpp"

int main(void) {
    int size = 5;
    Graph graph(Vector2(size, size));
    if (graph.readPointsFile("points.txt") == false) {
        return 1;
    }
    std::cout << graph << std::endl;
}