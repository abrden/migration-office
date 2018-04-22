#ifndef MIGRATION_OFFICE_ALERTSPAWNER_H
#define MIGRATION_OFFICE_ALERTSPAWNER_H

#include "SIGINTHandler.h"
#include "Spawner.h"

class AlertSpawner : public Spawner {

    private:
        Logger& logger;
        SIGINTHandler sigint_handler;

        Spawnables alerts;

    public:
        AlertSpawner(Logger& logger, const std::string& alerts_file);
        void spawn(std::string spawnable) override;
        bool quit() override;
        ~AlertSpawner() override;

};


#endif //MIGRATION_OFFICE_ALERTSPAWNER_H
