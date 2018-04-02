#include "Spawnables.h"

Spawnables::const_iterator Spawnables::begin() {
    return items.begin();
}

Spawnables::const_iterator Spawnables::end() {
    return items.end();
}

Spawnables::const_iterator Spawnables::erase(Spawnables::const_iterator iterator) {
    return items.erase(iterator);
}

void Spawnables::sort_by_ascending_timestamp() {
    items.sort();
}

bool Spawnables::empty() {
    return items.empty();
}

std::list<std::pair<int, Spawnable*>>& Spawnables::get_items() {
    return items;
}

Spawnables::~Spawnables() {
    while (!items.empty()) {
        delete items.back().second;
        items.pop_back();
    }
}

