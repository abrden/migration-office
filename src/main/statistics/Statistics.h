#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include "SharedMemory.h"
#include "ExclusiveLock.h"

#include <array>

typedef struct {
    size_t allowed_residents;
    size_t detained_residents;
    size_t allowed_foreigners;
    size_t deported_foreigners;
} Data;

class Statistics {

    private:
        Data data;
        SharedMemory<Data> stats_shm;
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
