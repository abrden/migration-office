#include "Spawner.h"

#include <ctime>
#include <unistd.h>
#include <iostream>

Spawner::Spawner(Logger& logger, Spawnables& items) : logger(logger), items(items) {}

void Spawner::run() {
    items.sort_by_ascending_timestamp();

    std::time_t t0 = std::time(nullptr);

    while (!items.empty() && !quit()) {
        std::time_t next_timestamp = items.front().first;
        logger(SPAWNER) << "The next timestamp is: "<< next_timestamp << std::endl;

        std::time_t t = std::time(nullptr);
        long int sleep_time = next_timestamp - (t - t0);
        logger(SPAWNER) << "The sleep times is: "<< sleep_time << std::endl;

        if (sleep_time > 0) sleep((unsigned)sleep_time);

        for (Spawnables::iterator iterator = items.begin(), end = items.end();
             iterator != end && (*iterator).first == next_timestamp;
             ++iterator) {

            logger(SPAWNER) << "I slept " << sleep_time << " - Spawning item with timestamp " << (*iterator).first << std::endl;
            spawn((*iterator).second);
            iterator = items.erase(iterator);
        }
    }

    logger(SPAWNER) << "I'm done spawning" << std::endl;
}
