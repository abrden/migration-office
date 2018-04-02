#include "Spawner.h"
#include "WantedPersonAlert.h"

#include <ctime>
#include <iostream>

template class Spawner<WantedPersonAlert>;

template <class T>
Spawner<T>::Spawner(std::list<std::pair<int, T*>>& items) : items(items) {
    items.sort();
}

template <class T>
void Spawner<T>::run() {
    std::time_t t0 = std::time(0);

    while (!items.empty()) {
        std::time_t t = std::time(0);

        for (typename std::list<std::pair<int, T*>>::const_iterator iterator = items.begin(), end = items.end();
             iterator != end && (*iterator).first <= (t - t0);
             ++iterator) {
            // TODO Spawn the item! Add to WantedPersonsList
            std::cout << "Time passed: " << (t - t0) << " - Spawning item with timestamp " << (*iterator).first << std::endl;
            delete (*iterator).second; // FIXME temporary deletion to avoid mem leak
            iterator = items.erase(iterator);
        }
    }
}

template <class T>
Spawner<T>::~Spawner() {}