#pragma once
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <limits>
#include <utility>
#include "Node.hpp"
#include "Rail.hpp"
#include "Train.hpp"
#include "RailwayCollection.hpp"

class Pathfinding {
    std::unordered_map<LinkablePart*, float> gScore;
    std::unordered_map<LinkablePart*, LinkablePart*>  parent;
    std::unordered_set<LinkablePart*>        closed;

    LinkablePart* start = nullptr;
    LinkablePart* goal  = nullptr;
    float waitTime = 0.0f;

    float edgeCost(LinkablePart* to) const {
        if (auto rail = dynamic_cast<Rail*>(to)) {
            if (!rail->isSegmentEmpty())
                return std::numeric_limits<float>::infinity();
    
            float refSpeed = rail->getSpeedLimit();
    
            if (refSpeed <= 0.0f) refSpeed = 1.0f;
    
            return rail->getLength() / refSpeed;
        }
        if (dynamic_cast<Node*>(to))
            return waitTime; 
    
        return std::numeric_limits<float>::infinity();
    }
    

public:
    std::list<LinkablePart*> dijkstra(Train* train) {
        start    = train->getDeparture();
        goal     = train->getArrival();
        waitTime = train->getStopDuration().toFloat();

        gScore.clear(); parent.clear(); closed.clear();

        auto  inf = std::numeric_limits<float>::infinity();
        auto& nodes = NodeCollection::getInstance().getElements();
        auto& rails = RailCollection::getInstance().getElements();

        for (LinkablePart* p : nodes) gScore[p] = inf;
        for (LinkablePart* p : rails) gScore[p] = inf;
        gScore[start] = 0.f;

        auto cmp = [](const std::pair<float, LinkablePart*>& a, const std::pair<float, LinkablePart*>& b){ return a.first > b.first; };
        std::priority_queue<std::pair<float, LinkablePart*>, std::vector<std::pair<float, LinkablePart*>>, decltype(cmp)> open(cmp);
        open.emplace(0.f, start);

        while (!open.empty()) {
            auto [dist, current] = open.top(); open.pop();
            if (closed.contains(current)) continue;
            closed.insert(current);

            if (current == goal) break;

            for (LinkablePart* neighbour : current->getConnectedParts()) {
                if (closed.contains(neighbour)) continue;

                float tentative = dist + edgeCost(neighbour);
                if (tentative < gScore[neighbour]) {
                    gScore[neighbour] = tentative;
                    parent[neighbour] = current;
                    open.emplace(tentative, neighbour);
                }
            }
        }

        std::list<LinkablePart*> path;
        if (!parent.contains(goal) && start != goal) {
            return path;
        } 

        for (LinkablePart* p = goal; p != nullptr; p = parent.contains(p) ? parent[p] : nullptr)
            path.push_front(p);

        // for (const auto& p : path) {
        //     if (auto rail = dynamic_cast<Rail*>(p)) {
        //         std::cout << "  " << rail->getId();
        //     } else if (auto node = dynamic_cast<Node*>(p)) {
        //         std::cout << " " << node->getName();
        //     } else {
        //         std::cout << " Unknown part";
        //     }
        // }
        // std::cout << std::endl;

        return path;
    }
};
