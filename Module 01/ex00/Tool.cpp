#include "Tool.hpp"

void Tool::decreaseDurability() {
    if (numberOfUses > 0) {
        numberOfUses--;
    } else {
        LOG_VERBOSE("* The tool has broken *");
    }
}

void Hammer::use() {
    decreaseDurability();
    LOG_VERBOSE("* Smashing with hammer ! *");
}

void Shovel::use() {
    decreaseDurability();
    LOG_VERBOSE("* Digging with shovel *");
}