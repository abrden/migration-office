#ifndef MIGRATION_OFFICE_SPAWNER_H
#define MIGRATION_OFFICE_SPAWNER_H

#include <list>
#include <utility>
#include <string>

#include "Spawnables.h"
#include "ConfigurationFileReader.h"

class Spawner {

    private:
        Spawnables& items;

    public:
        explicit Spawner(Spawnables& items);
        void run();
        virtual void spawn(std::string spawnable) = 0;
        virtual bool quit() = 0;
        virtual ~Spawner() = default;

};


#endif //MIGRATION_OFFICE_SPAWNER_H
