#ifndef MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H
#define MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H

#include "SharedMemoryArray.h"
#include "ExclusiveLock.h"
#include "FifoReader.h"
#include "FifoWriter.h"
#include "StatisticsData.h"

class StatisticsCommunicator {

    private:
        SharedMemoryArray<size_t> shm;
        ExclusiveLock lock;

        void increment_field(size_t pos);

    public:
        StatisticsCommunicator();
        void notify_allowed_resident();
        void notify_detained_resident();
        void notify_allowed_foreigner();
        void notify_deported_foreigner();
};

#endif //MIGRATION_OFFICE_STATISTICSCOMMUNICATOR_H
