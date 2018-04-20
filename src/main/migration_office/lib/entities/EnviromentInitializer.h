#ifndef MIGRATION_OFFICE_ENVIROMENTINITIALIZER_H
#define MIGRATION_OFFICE_ENVIROMENTINITIALIZER_H

#include "StatisticsData.h"
#include "SharedMemory.h"


class EnviromentInitializer {
    private:
        SharedMemory<StatisticsData> stats_shm;

    public:
        EnviromentInitializer();
        void initialize();
};

#endif //MIGRATION_OFFICE_ENVIROMENTINITIALIZER_H
