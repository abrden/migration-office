#include "Spawner.h"

Spawner::Spawner(std::list<std::pair<int, Spawnable*>>& items) : items(items) {
    items.sort();
}

void Spawner::run() {
    // TODO
}

Spawner::~Spawner() {}