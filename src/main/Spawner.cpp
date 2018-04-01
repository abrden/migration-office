#include "Spawner.h"

Spawner::Spawner(const std::string& file_path) {
    items = load_items(file_path);
    items.sort();
}

void Spawner::run() {
    // TODO
}

const std::list<std::pair<int, Spawnable*>>& Spawner::get_items() {
    return items;
}

Spawner::~Spawner() {
    while (!items.empty()) {
        delete items.back().second;
        items.pop_back();
    }
}