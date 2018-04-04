#ifndef MIGRATION_OFFICE_SPAWNER_H
#define MIGRATION_OFFICE_SPAWNER_H

#include <list>
#include <utility>
#include "Spawnables.h"

class Spawner {

    private:
        Spawnables& items;

    public:
        explicit Spawner(Spawnables& items);
        void run();
        ~Spawner() = default;

};


#endif //MIGRATION_OFFICE_SPAWNER_H
