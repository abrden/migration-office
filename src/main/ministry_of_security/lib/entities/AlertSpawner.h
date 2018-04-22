#ifndef MIGRATION_OFFICE_ALERTSPAWNER_H
#define MIGRATION_OFFICE_ALERTSPAWNER_H

#include "SharedMemory.h"
#include "SIGINTHandler.h"
#include "AlertData.h"
#include "Spawner.h"

class AlertSpawner : public Spawner {

    private:
        Logger& logger;
        SIGINTHandler sigint_handler;

        SharedMemory<AlertData> shmem;
        ExclusiveLock shmem_lock;
        Spawnables alerts;
        const size_t booths_number;
        const std::vector<pid_t> booths_ids;

    public:
        AlertSpawner(Logger& logger, const std::string& alerts_file, const size_t booths_number, const std::vector<pid_t>& booths_ids);
        void spawn(std::string spawnable) override;
        bool quit() override;
        ~AlertSpawner() override;

};


#endif //MIGRATION_OFFICE_ALERTSPAWNER_H
