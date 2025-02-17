#include "Worker.hpp"
#include "Workshop.hpp"
#include "Tool.hpp"
#include "Logger.hpp"

int main() {
    LOG_VERBOSE("===== Initialisation des objets =====");

    Worker w1;
    Worker w2;
    Worker w3;

    Shovel shovel = Shovel(5);
    Hammer hammer = Hammer(3);

    Workshop ws1;
    Workshop ws2;

    LOG_VERBOSE("===== Attribution des outils =====");
    w1.addTool(&shovel);
    w2.addTool(&hammer);

    LOG_VERBOSE("===== Transfert d'outils =====");
    w1.giveTool(w2, &shovel);

    LOG_VERBOSE("===== Inscriptions aux Workshops =====");
    w1.joinWorkShop(ws1);
    w2.joinWorkShop(ws1);
    w3.joinWorkShop(ws2);  

    LOG_VERBOSE("===== Début de la journée de travail =====");
    ws1.executeWorkDay();
    ws2.executeWorkDay();

    LOG_VERBOSE("===== Retrait des Workers =====");
    w1.leaveWorkShop(ws1);

    LOG_VERBOSE("===== Fin du test =====");

    return 0;
}
