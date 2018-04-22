#ifndef MIGRATION_OFFICE_ALERTSPAWNER_H
#define MIGRATION_OFFICE_ALERTSPAWNER_H

#include "SharedMemory.h"
#include "SIGINTHandler.h"
#include "Spawner.h"

const static size_t BUFFSIZE = 1024;

typedef struct {
    char serialized_alert[BUFFSIZE];
    size_t serialized_alert_size;
    size_t read_by_quantity;
} AlertData;

class AlertSpawner : public Spawner {

    private:
        Logger& logger;
        SIGINTHandler sigint_handler;

        SharedMemory<AlertData> shmem;
        ExclusiveLock shmem_lock;
        Spawnables alerts;

    public:
        AlertSpawner(Logger& logger, const std::string& alerts_file);
        void spawn(std::string spawnable) override;
        bool quit() override;
        ~AlertSpawner() override;

};


#endif //MIGRATION_OFFICE_ALERTSPAWNER_H
