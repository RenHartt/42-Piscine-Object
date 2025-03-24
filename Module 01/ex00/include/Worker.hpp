#pragma once

#include "Tool.hpp"
#include "Logger.hpp"
#include "IWorkshop.hpp"
#include <set>

struct Position {
    Position(int x = 0, int y = 0, int z = 0): x(x), y(y), z(z) {}
    int x, y, z;
};

struct Statistic {
    Statistic(int level = 0, int exp = 0): level(level), exp(exp) {}
    int level, exp;
};

class Worker {
    public:
        Worker(): position(0, 0), statistic(1, 0) { LOG_VERBOSE("* Worker created *"); }

        template<typename ToolType>
        ToolType* GetTool();

        bool hasTool(const std::type_info& type) const;

        void addTool(Tool* tool);
        void removeTool(Tool* tool);
        void giveTool(Worker& worker, Tool* tool);

        void joinWorkShop(IWorkshop& workshop);
        void leaveWorkShop(IWorkshop& workshop);
        
        template<typename ToolType>
        void work();

    private:
        Position position;
        Statistic statistic;
        std::set<Tool*> tools;
        std::set<IWorkshop*> workshops;
};

#include "Worker.tpp"