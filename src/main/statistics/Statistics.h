#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include "SharedMemory.h"
#include "ExclusiveLock.h"
#include "StatisticsData.h"
#include "FifoWriter.h"

#include <array>

class Statistics {

    private:
        const size_t booths_number;
        SharedMemory<StatisticsData> stats_shm;
        ExclusiveLock stats_shm_lock;
        FifoWriter fifo;

        void initialize_data();
        void send_initialized_data_confirmation();
        StatisticsData update_data();

    public:
        explicit Statistics(size_t booths_number);
        size_t get_allowed_residents();
        size_t get_detained_residents();
        size_t get_allowed_foreigners();
        size_t get_deported_foreigners();

};

#endif //MIGRATION_OFFICE_STATISTICS_H
