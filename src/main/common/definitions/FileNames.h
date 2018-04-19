#ifndef MIGRATION_OFFICE_FILENAMES_H
#define MIGRATION_OFFICE_FILENAMES_H

#include <string>

namespace BinaryNames {
    extern const std::string BOOTH_BINARY = "./migration_booth";
    extern const std::string SPAWNER_BINARY = "./migration_spawner";
    extern const std::string MINISTER_BINARY = "./ministry_of_security";
    extern const std::string STATISTICS_BINARY = "./statistics";
}

namespace StatisticsSharedMemory {
    extern const std::string STATS_FILE = "/bin/ls";
    extern const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
    extern const char LETTER = 'A';
}

#endif //MIGRATION_OFFICE_FILENAMES_H
