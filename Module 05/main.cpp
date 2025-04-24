#include <iostream>

#include "Simulation.hpp"

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
    
    for (const auto& train : TrainCollection::getInstance().getElements()) {
        Simulation::getInstance().attach(train);
    }
    
    const Time& globalTime = Simulation::getInstance().getGlobalTime();
    
    while (globalTime.toFloat() < 24 * 3600) {
        Simulation::getInstance().update(Time(0, 0, 1));
        // std::cout << "---------- Rail Segment ----------" << std::endl;
        // RailCollection::getInstance().print();
    }
    
    // std::cout << "Rail network and train composition parsed successfully." << std::endl;
    // std::cout << "---------- Train ----------" << std::endl;
    // TrainCollection::getInstance().print();
    // std::cout << "---------- Rail Segment ----------" << std::endl;
    // RailCollection::getInstance().print();
    // std::cout << "---------- Node ----------" << std::endl;
    // NodeCollection::getInstance().print();

    return EXIT_SUCCESS;
}