#pragma once

#include "Tool.hpp"
#include "Logger.hpp"
#include "Workshop.hpp"
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
        Worker(): position(0, 0), statistic(1, 0) { LOG_VERBOSE("* Worker created *"); }

        template<typename ToolType>
        ToolType* GetTool();

        void addTool(Tool* tool);
        void removeTool(Tool* tool);
        void giveTool(Worker& worker, Tool* tool);

        void joinWorkShop(Workshop& workshop);
        void leaveWorkShop(Workshop& workshop);
        
        void work();

    private:
        Position position;
        Statistic statistic;
        std::set<Tool*> tools;
        std::set<Workshop*> workshops;
};