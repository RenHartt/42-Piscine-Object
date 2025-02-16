#pragma once

#include "Tool.hpp"
#include "Logger.hpp"
#include <set>

class Workshop;

struct Position {
    Position(int x, int y): x(x), y(y) {}
    int x, y;
};

struct Statistic {
    Statistic(int level, int exp): level(level), exp(exp) {}
    int level, exp;
};

class Worker {
    public:
        Worker(): position(0, 0), statistic(1, 0) {}

        void addTool(Tool* tool) { if (tool) this->tools.insert(tool); }
        void removeTool(Tool* tool) { if (tool) this->tools.erase(tool); }
        void giveTool(Worker* worker, Tool* tool) {
            if (!worker || !tool || worker == this) return;

            if (this->tools.find(tool) != this->tools.end()) {
                this->removeTool(tool);
                worker->addTool(tool);
                LOG_VERBOSE("Tool has been transferred to another worker!");
            } else {
                LOG_VERBOSE("Error: Worker does not own this tool!");
            }
        }

        void submitApplication(const Workshop& workshop);
        
    private:
        Position position;
        Statistic statistic;
        std::set<Tool*> tools;
        std::set<Workshop*> workshops;
};