#ifndef MIGRATION_OFFICE_SPAWNER_H
#define MIGRATION_OFFICE_SPAWNER_H

#include "Spawnable.h"

#include <list>
#include <string>
#include <utility>

class Spawner {

    private:
        std::list<std::pair<int, Spawnable*>>& items;

    public:
        explicit Spawner(std::list<std::pair<int, Spawnable*>>& items);
        void run();
        ~Spawner();

};


#endif //MIGRATION_OFFICE_SPAWNER_H
