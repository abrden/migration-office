#ifndef MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H
#define MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H

#include "SharedMemory.h"
#include "ExclusiveLock.h"
#include "StatisticsData.h"

class StatisticsCommunicator {

    private:
        SharedMemory<StatisticsData> stats_shm;
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
