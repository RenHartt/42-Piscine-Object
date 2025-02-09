#include "ex01.hpp"

int main(void) {
    Graph graph({9, 9});
    for (float i = 0; i <= 9; i++) {
        graph.addPoint({i, i});
    }
    std::cout << graph << std::endl;
}