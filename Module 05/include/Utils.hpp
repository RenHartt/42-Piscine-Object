#pragma once

#include <unordered_set>

template<typename T, typename U>
std::unordered_set<T*> castToSet(const std::unordered_set<U*>& inputSet) {
    std::unordered_set<T*> outputSet;
    for (const auto& item : inputSet) {
        if (T* castedItem = dynamic_cast<T*>(item)) {
            outputSet.insert(castedItem);
        }
    }
    return outputSet;
}