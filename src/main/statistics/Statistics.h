#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include "SharedMemory.h"
#include "ExclusiveLock.h"
#include "StatisticsData.h"
#include "FifoReader.h"
#include "FifoWriter.h"
#include "Logger.h"
#include "SIGINTHandler.h"

#include <array>

class Statistics {

    private:
        Logger logger;

        const size_t booths_number;
        SIGINTHandler sigint_handler;
        SharedMemory<StatisticsData> shm;
        ExclusiveLock lock;
        FifoWriter fifo;
        FifoReader cnf_fifo;

        void initialize_data();
        void send_initialized_data_confirmation();
        void wait_for_booths();
        StatisticsData update_data();
        size_t get_allowed_residents();
        size_t get_detained_residents();
        size_t get_allowed_foreigners();
        size_t get_deported_foreigners();

    public:
        Statistics(size_t booths_number, const bool debug, const std::string& log_file);
        void start();
        ~Statistics();
};

#endif //MIGRATION_OFFICE_STATISTICS_H
