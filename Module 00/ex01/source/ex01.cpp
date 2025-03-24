#include "ex01.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cmath>

std::string intToString(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    int X = static_cast<int>(round(graph.getSize().getX()));
    int Y = static_cast<int>(round(graph.getSize().getY()));

    std::vector<std::vector<char> > grid(Y + 1, std::vector<char>(X * 2 + 2, ' '));

    for (int i = 0; i <= Y; i++) {
        for (int j = 0; j <= X; j++) {
            grid[i][j * 2] = '.';
        }
    }

    std::vector<Vector2>::const_iterator it = graph.getPoints().begin();
    while (it != graph.getPoints().end()) {
        int gridX = static_cast<int>(round(it->getX()));
        int gridY = static_cast<int>(round(it->getY()));

        if (gridX >= 0 && gridX <= X && gridY >= 0 && gridY <= Y) {
            grid[Y - gridY][gridX * 2] = 'X';
        }
        ++it;
    }

    for (int i = 0; i <= Y; i++) {
        std::string num = intToString(Y - i);
        grid[i].insert(grid[i].begin(), num.begin(), num.end());
        grid[i].insert(grid[i].begin() + num.size(), ' ');
    }

    std::string xAxis = "  ";
    for (int i = 0; i <= X; i++) {
        xAxis += intToString(i) + " ";
    }

    std::string output;
    for (size_t i = 0; i < grid.size(); ++i) {
        output.append(grid[i].begin(), grid[i].end());
        output.push_back('\n');
    }
    output.append(xAxis);

    os << output;
    return os;
}
