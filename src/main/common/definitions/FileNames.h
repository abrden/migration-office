#ifndef MIGRATION_OFFICE_FILENAMES_H
#define MIGRATION_OFFICE_FILENAMES_H

#include <string>

namespace BinaryNames {
    const std::string BOOTH_BINARY = "./migration_booth";
    const std::string SPAWNER_BINARY = "./migration_spawner";
    const std::string MINISTER_BINARY = "./ministry_of_security";
    const std::string STATISTICS_BINARY = "./statistics";
}

namespace StatisticsSharedMemory {
    const std::string STATS_FILE = "/bin/ls";
    const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
    const std::string FIFO_FILE = "/tmp/statistics_fifo";
    const std::string CNF_FIFO_FILE = "/tmp/statistics_cnf_fifo";
    const char LETTER = 'A';
}

namespace AlertsSharedMemory {
    const std::string SHMEM_FILE = "/bin/cat";
    const std::string LOCK_SHMEM_FILE = "/tmp/spawner_shm_lock";
    const char LETTER = 'B';
}

#endif //MIGRATION_OFFICE_FILENAMES_H
