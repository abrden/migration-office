#include "Spawner.h"
#include "WantedPersonAlert.h"

#include <ctime>
#include <iostream>

Spawner::Spawner(Spawnables& items) : items(items) {
    items.sort_by_ascending_timestamp();
}

void Spawner::run() {
    std::time_t t0 = std::time(nullptr);

    while (!items.empty()) {
        std::time_t t = std::time(nullptr);

        for (Spawnables::iterator iterator = items.begin(), end = items.end();
             iterator != end && (*iterator).first <= (t - t0);
             ++iterator) {
            // TODO Spawn the item! Add to WantedPersonsList
            std::cout << "Time passed: " << (t - t0) << " - Spawning item with timestamp " << (*iterator).first << std::endl;
            delete (*iterator).second; // FIXME temporary deletion to avoid mem leak
            iterator = items.erase(iterator);
        }
    }

    std::cout << "I'm done spawning" << std::endl;
}
