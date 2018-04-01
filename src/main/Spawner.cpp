#include "Spawner.h"

template <class T>
Spawner<T>::Spawner(std::list<std::pair<int, T*>>& items) : items(items) {
    items.sort();
}

template <class T>
void Spawner<T>::run() {
    // TODO
}

template <class T>
Spawner<T>::~Spawner() {}