#include <iostream>

#include "Simulation.hpp"
#include "RandomEvent.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <rail_network_file> <train_composition_file>" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        Simulation::parseRailNetwork(argv[1]);
        Simulation::parseTrainComposition(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    RandomEvent randomEvent;
    Simulation& sim = Simulation::getInstance();
    TrainCollection& trains = TrainCollection::getInstance();
    RailCollection& rails = RailCollection::getInstance();
    NodeCollection& nodes = NodeCollection::getInstance();
    const Time& globalTime = sim.getGlobalTime();
    
    for (const auto& train : trains.getElements()) sim.attach(train);
    for (const auto& rail : rails.getElements()) randomEvent.addRailObserver(rail);
    for (const auto& node : nodes.getElements()) randomEvent.addNodeObserver(node);

    while (globalTime < Time(24, 0, 0)) {
        randomEvent.randomEvent(10.f);
        sim.update(Time(0, 0, 1));
    }

    return EXIT_SUCCESS;
}