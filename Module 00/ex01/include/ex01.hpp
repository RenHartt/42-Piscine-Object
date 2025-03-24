#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <regex.h>

class Vector2 {
private:
    float X, Y;

public:
    Vector2(): X(0), Y(0) {}
    Vector2(float X, float Y): X(X), Y(Y) {}

    float getX(void) const { return X; }
    float getY(void) const { return Y; }
    void setX(float X) { this->X = X; }
    void setY(float Y) { this->Y = Y; }
};

class Graph {
public:
    Graph(): size(Vector2(0, 0)), points(0) {}
    Graph(const Vector2& size): size(size), points(0) {}
    Graph(const std::vector<Vector2>& points): size(Vector2(0, 0)), points(points) {}
    Graph(const Vector2& size, const std::vector<Vector2>& points): size(size), points(points) {}

    const Vector2& getSize(void) const { return size; }
    const std::vector<Vector2>& getPoints(void) const { return points; }

    void addPoint(const Vector2& point) { points.push_back(point); }
    bool validFile(const std::string& filename) {
        std::ifstream file;
        file.open(filename.c_str());
        if (!file.is_open()) {
            return false;
        }
        std::string line;
        std::string pattern("^-?[0-9]+.?[0-9]* -?[0-9]+.?[0-9]*$");
        regex_t regex;
        regcomp(&regex, pattern.c_str(), REG_EXTENDED);
        while (getline(file, line)) {
            if (regexec(&regex, line.c_str(), 0, NULL, 0) != 0) {
                return false;            
            }
        }
        regfree(&regex);
        file.close();
        return true;
    }
    bool readPointsFile(const std::string& filename) {
        std::ifstream file;
        file.open(filename.c_str());
        if (!file.is_open()) {
            std::cerr << "Cannot open file: " << filename << std::endl;
            return false;
        } else if (!validFile(filename)) {
            std::cerr << "Invalid file: " << filename << std::endl;
            std::cerr << "File must contain points in the format: X Y" << std::endl;
            return false;
        }
        while (!file.eof()) {
            float X, Y;
            file >> X >> Y;
            addPoint(Vector2(X, Y));
        }
        file.close();
        return true;
    }

private:
    Vector2 size;
    std::vector<Vector2> points;
};

std::ostream& operator<<(std::ostream& os, const Graph& graph);