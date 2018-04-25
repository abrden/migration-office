#ifndef MIGRATION_OFFICE_ALERTSPAWNER_H
#define MIGRATION_OFFICE_ALERTSPAWNER_H

#include "SharedMemory.h"
#include "SIGINTHandler.h"
#include "AlertData.h"
#include "Spawner.h"
#include "SharedMemoryArray.h"
#include "AlertsSharedMemory.h"

#include <vector>

class AlertSpawner : public Spawner {

    private:
        Logger& logger;
        SIGINTHandler sigint_handler;

        AlertsSharedMemory alerts_shm;
        ExclusiveLock alerts_shmem_lock;
        Spawnables alerts;
        const size_t booths_number;
        const std::vector<pid_t> booths_ids;

        size_t find_new_alert_index();

    public:
        AlertSpawner(Logger& logger, const std::string& alerts_file, const size_t booths_number, const std::vector<pid_t>& booths_ids);
        void spawn(std::string spawnable) override;
        bool quit() override;
        ~AlertSpawner() override;

};


#endif //MIGRATION_OFFICE_ALERTSPAWNER_H
