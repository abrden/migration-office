#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include <cstddef>
#include "SharedMemory.h"
#include <array>
#include "ExclusiveLock.h"

class Statistics {

    private:
        std::array<size_t, 4> data;
        SharedMemory<size_t[4]> stats_shm;
        ExclusiveLock stats_shm_lock;

        void update_data();

    public:
        Statistics();
        size_t get_allowed_residents();
        size_t get_detained_residents();
        size_t get_allowed_foreigners();
        size_t get_deported_foreigners();

};

#endif //MIGRATION_OFFICE_STATISTICS_H
