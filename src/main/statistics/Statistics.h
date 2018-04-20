#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include "SharedMemory.h"
#include "ExclusiveLock.h"
#include "StatisticsData.h"

#include <array>

class Statistics {

    private:
        SharedMemory<Data> stats_shm;
        ExclusiveLock stats_shm_lock;

        Data update_data();

    public:
        Statistics();
        size_t get_allowed_residents();
        size_t get_detained_residents();
        size_t get_allowed_foreigners();
        size_t get_deported_foreigners();

};

#endif //MIGRATION_OFFICE_STATISTICS_H
