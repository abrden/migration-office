#include "Spawner.h"

#include <ctime>
#include <iostream>

Spawner::Spawner(Logger& logger, Spawnables& items) : logger(logger), items(items) {}

void Spawner::run() {
    items.sort_by_ascending_timestamp();

    std::time_t t0 = std::time(nullptr);

    while (!items.empty() && !quit()) {
        std::time_t t = std::time(nullptr);

        for (Spawnables::iterator iterator = items.begin(), end = items.end();
             iterator != end && (*iterator).first <= (t - t0);
             ++iterator) {
            spawn((*iterator).second);
            logger(SPAWNER) << "Time passed: " << (t - t0) << " - Spawning item with timestamp " << (*iterator).first << std::endl;
            iterator = items.erase(iterator);
        }
    }

    logger(SPAWNER) << "I'm done spawning" << std::endl;
}
