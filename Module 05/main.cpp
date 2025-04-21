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

    std::cout << "Rail network and train composition parsed successfully." << std::endl;
    std::cout << "---------- Train ----------" << std::endl;
    TrainCollection::getInstance().print();
    std::cout << "---------- Rail Segment ----------" << std::endl;
    RailCollection::getInstance().print();
    std::cout << "---------- Node ----------" << std::endl;
    NodeCollection::getInstance().print();

    return EXIT_SUCCESS;
}