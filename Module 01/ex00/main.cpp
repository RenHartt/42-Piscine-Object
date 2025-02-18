#include "Worker.hpp"
#include "Tool.hpp"
#include "Workshop.hpp"
#include <iostream>

int main() {
    LOG_VERBOSE("===== Initialisation des Workers et Outils =====");

    // Création des Workers
    Worker w1, w2, w3;

    // Création des outils avec des durabilités différentes
    Shovel* shovel1 = new Shovel(3); // 3 utilisations avant de casser
    Shovel* shovel2 = new Shovel(2); // 2 utilisations
    Hammer* hammer1 = new Hammer(4); // 4 utilisations

    // Attribution des outils aux Workers
    w1.addTool(shovel1);
    w2.addTool(shovel2);
    w3.addTool(hammer1);

    LOG_VERBOSE("===== Création des Workshops =====");

    // Création des Workshops spécialisés
    Workshop<Shovel> wsShovel;
    Workshop<Hammer> wsHammer;

    LOG_VERBOSE("===== Inscription des Workers aux Workshops =====");

    // Inscription des Workers aux Workshops correspondant à leurs outils
    w1.joinWorkShop(wsShovel);
    w2.joinWorkShop(wsShovel);
    w3.joinWorkShop(wsHammer);

    LOG_VERBOSE("===== Début du cycle de travail =====");

    int day = 1;
    while (true) {
        LOG_VERBOSE("===== JOUR " + std::to_string(day) + " =====");

        wsShovel.executeWorkDay();
        wsHammer.executeWorkDay();

        std::cout << wsShovel.workers.size();
        std::cout << wsHammer.workers.size();

        // Vérifier si tous les Workers sont sortis des Workshops
        if (wsShovel.workers.empty() && wsHammer.workers.empty()) {
            LOG_VERBOSE("===== Tous les Workers ont terminé, fin du test =====");
            break;
        }

        day++;
    }

    return 0;
}
