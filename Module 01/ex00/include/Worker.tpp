#pragma once

#include "Worker.hpp"

template <typename ToolType>
ToolType* Worker::GetTool() {  // ✅ Ajout de `Worker::`
    for (std::set<Tool*>::iterator it = this->tools.begin(); it != this->tools.end(); ++it) {
        if (dynamic_cast<ToolType*>(*it)) {
            return dynamic_cast<ToolType*>(*it);
        }
    }
    return NULL;
}

template <typename ToolType>
void Worker::work() {  // ✅ Ajout de `Worker::`
    LOG_VERBOSE("* Worker doing work *");

    ToolType* tool = this->GetTool<ToolType>();  // ✅ Utilisation correcte de `this->`
    if (!tool) {
        LOG_VERBOSE("* Worker has no valid tool for this Workshop *");
        return;
    }

    tool->use();

    if (tool->getNumberOfUses() <= 0) {
        LOG_VERBOSE("* Tool is broken and removed *");
        this->tools.erase(tool);  // ✅ Accès correct aux membres de la classe
        delete tool;

        if (!this->GetTool<ToolType>()) {
            LOG_VERBOSE("* Worker removed from Workshop due to missing tool *");

            for (std::set<IWorkshop*>::iterator it = this->workshops.begin(); it != this->workshops.end();) {
                std::set<IWorkshop*>::iterator toErase = it++;  // ✅ Avance l'itérateur AVANT suppression

                if ((*toErase)->getRequiredToolType() == typeid(ToolType)) {
                    (*toErase)->deleteWorker(*this);
                }
            }
        }
    }
}
