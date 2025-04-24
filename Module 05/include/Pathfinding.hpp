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
private:
    std::unordered_map<LinkablePart*, float> gScore;
    std::unordered_map<LinkablePart*, LinkablePart*> parent;
    std::unordered_set<LinkablePart*> closed;

    LinkablePart* start = nullptr;
    LinkablePart* goal  = nullptr;
    float waitTime = 0.0f;

    float edgeCost(LinkablePart* to) const {
        if (auto rail = dynamic_cast<Rail*>(to)) {
            return rail->getLength() / rail->getSpeedLimit();
        } else if (dynamic_cast<Node*>(to)) {
            return waitTime; 
        }
        return std::numeric_limits<float>::infinity();
    }
public:
    std::list<LinkablePart*> dijkstra(Train* train) {
        start = train->getCurrentPart();
        goal = train->getArrival();
        waitTime = train->getStopDuration().toFloat();
        if (start == nullptr || goal == nullptr || start == goal) return {};

        gScore.clear(); parent.clear(); closed.clear();
        auto& nodes = NodeCollection::getInstance().getElements();
        auto& rails = RailCollection::getInstance().getElements();
        for (LinkablePart* p : nodes) gScore[p] = std::numeric_limits<float>::infinity();
        for (LinkablePart* p : rails) gScore[p] = std::numeric_limits<float>::infinity();
        gScore[start] = 0.f;

        auto cmp = [](const std::pair<float, LinkablePart*>& a, const std::pair<float, LinkablePart*>& b){ return a.first > b.first; };
        std::priority_queue<std::pair<float, LinkablePart*>, std::vector<std::pair<float, LinkablePart*>>, decltype(cmp)> open(cmp);
        open.emplace(0.f, start);

        while (!open.empty()) {
            auto [dist, current] = open.top(); open.pop();
            if (closed.count(current)) continue;
            closed.insert(current);
            if (current == goal) break;

            bool firstStep = (current == start);

            for (LinkablePart* neighbour : current->getConnectedParts()) {
                if (closed.count(neighbour)) continue;

                if (Rail* rail = dynamic_cast<Rail*>(neighbour)) {
                    if (rail->isClosedRail()) continue;
                    if (firstStep && !rail->isSegmentEmpty()) continue;
                }

                float tentative = dist + edgeCost(neighbour);
                if (tentative < gScore[neighbour]) {
                    gScore[neighbour] = tentative;
                    parent[neighbour] = current;
                    open.emplace(tentative, neighbour);
                }
            }
        }

        std::list<LinkablePart*> path;
        if (!parent.count(goal) && start != goal) {
            return path;
        } 

        for (LinkablePart* p = goal; p != nullptr; p = parent.count(p) ? parent[p] : nullptr)
            path.push_front(p);

        return path;
    }
};
