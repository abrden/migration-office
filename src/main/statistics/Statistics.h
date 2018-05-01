#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include "SharedMemoryArray.h"
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

        SIGINTHandler sigint_handler;
        SharedMemoryArray<size_t> shm;
        ExclusiveLock lock;

        size_t get_field(size_t pos);

    public:
        Statistics(const bool debug, const std::string& log_file);
        void start();
        ~Statistics();
};

#endif //MIGRATION_OFFICE_STATISTICS_H
