#ifndef MIGRATION_OFFICE_ALERTDELETER_H
#define MIGRATION_OFFICE_ALERTDELETER_H

#include "AlertsSharedMemory.h"
#include "Spawner.h"
#include "SIGINTHandler.h"

class AlertDeleter : public Spawner {
    private:
        Logger& logger;
        SIGINTHandler sigint_handler;

        AlertsSharedMemory alerts_shm;
        ExclusiveLock alerts_shmem_lock;
        Spawnables alerts;
    public:

        AlertDeleter(Logger& logger, const std::string& alerts_file);
        void spawn(std::string spawnable) override;
        virtual ~AlertDeleter();
};

#endif //MIGRATION_OFFICE_ALERTDELETER_H
