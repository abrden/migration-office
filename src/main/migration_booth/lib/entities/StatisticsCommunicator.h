#ifndef MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H
#define MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H

#include "SharedMemory.h"
#include "ExclusiveLock.h"

typedef struct {
    size_t allowed_residents;
    size_t detained_residents;
    size_t allowed_foreigners;
    size_t deported_foreigners;
} Data;

class StatisticsCommunicator {

    private:
        SharedMemory<Data> stats_shm;
        ExclusiveLock stats_shm_lock;

        void increment_field(size_t field);

    public:
        StatisticsCommunicator();
        void notify_allowed_resident();
        void notify_detained_resident();
        void notify_allowed_foreigner();
        void notify_deported_foreigner();
};

#endif //MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H
