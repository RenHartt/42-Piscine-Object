#include "ex01.hpp"
#include <cmath>
#include <sstream>
#include <vector>

std::string itoa(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    int X = std::round(graph.getSize().X);
    int Y = std::round(graph.getSize().Y);

    std::vector<std::vector<char>> grid(Y + 1, std::vector<char>(X * 2 + 2, ' '));

    for (int i = 0; i <= Y; i++) {
        for (int j = 0; j <= X; j++) {
            grid[i][j * 2] = '.';
        }
    }

    for (const Vector2& v : graph.getPoints()) {
        int gridX = std::round(v.X);
        int gridY = std::round(v.Y);

        if (gridX >= 0 && gridX <= X && gridY >= 0 && gridY <= Y) {
            grid[Y - gridY][gridX * 2] = 'X';
        }
    }

    for (int i = 0; i <= Y; i++) {
        std::string num = itoa(Y - i);
        grid[i].insert(grid[i].begin(), num.begin(), num.end());
        grid[i].insert(grid[i].begin() + num.size(), ' ');
    }

    std::string xAxis = "  ";
    for (int i = 0; i <= X; i++) {
        xAxis += itoa(i) + " ";
    }

    std::string output;
    for (const auto& row : grid) {
        output.append(row.begin(), row.end());
        output.push_back('\n');
    }
    output.append(xAxis);
    
    os << output;

    return os;
}
