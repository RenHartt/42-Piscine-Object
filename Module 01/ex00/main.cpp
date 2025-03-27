#include "Worker.hpp"
#include "Tool.hpp"
#include "Workshop.hpp"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

std::string itoa(int n)
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}


int main() {
    LOG_VERBOSE("===== Initialisation des Workers et Outils =====");

    Worker w1, w2, w3;

    Shovel* shovel1 = new Shovel(3);
    Shovel* shovel2 = new Shovel(2);
    Hammer* hammer1 = new Hammer(4);

    w1.addTool(shovel1);
    w2.addTool(shovel2);
    w3.addTool(hammer1);

    LOG_VERBOSE("===== Création des Workshops =====");

    Workshop<Shovel> wsShovel;
    Workshop<Hammer> wsHammer;

    LOG_VERBOSE("===== Inscription des Workers aux Workshops =====");

    w1.joinWorkShop(wsShovel);
    w2.joinWorkShop(wsShovel);
    w3.joinWorkShop(wsHammer);

    LOG_VERBOSE("===== Début du cycle de travail =====");

    
    for (int day = 1; wsShovel.getWorkshopSize() || wsHammer.getWorkshopSize(); day++) {
        LOG_VERBOSE("===== JOUR " + itoa(day) + " =====");

        wsShovel.executeWorkDay();
        wsHammer.executeWorkDay();
    }

    LOG_VERBOSE("===== Tous les Workers ont terminé, fin du test =====");

    return 0;
}
