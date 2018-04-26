#ifndef MIGRATION_OFFICE_SPAWNER_H
#define MIGRATION_OFFICE_SPAWNER_H

#include <string>

#include "Logger.h"
#include "Spawnables.h"

class Spawner {

    private:
        Logger& logger;
        Spawnables& items;

    public:
        Spawner(Logger& logger, Spawnables& items);
        void run();
        virtual void spawn(std::string spawnable) = 0;
        virtual bool quit() = 0;
        virtual ~Spawner() = default;

};


#endif //MIGRATION_OFFICE_SPAWNER_H
