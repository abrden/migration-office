#ifndef MIGRATION_OFFICE_FILENAMES_H
#define MIGRATION_OFFICE_FILENAMES_H

#include <string>

namespace OfficeDefaults {
    const int DEFAULT_BOOTHS_NUMBER = 10;
    const int DEFAULT_STAMPERS_NUMBER = 5;
    const std::string DEFAULT_LOG = "log";
}

namespace BinaryNames {
    const std::string ALERT_DELETER_BINARY = "./alert_deleter";
    const std::string BOOTH_BINARY = "./migration_booth";
    const std::string SPAWNER_BINARY = "./people_spawner";
    const std::string MINISTER_BINARY = "./ministry_of_security";
    const std::string STATISTICS_BINARY = "./statistics";
}

namespace StatisticsSharedMem {
    const std::string STATS_FILE = "/bin/ls";
    const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
    const std::string FIFO_FILE = "/tmp/statistics_fifo";
    const std::string CNF_FIFO_FILE = "/tmp/statistics_cnf_fifo";
    const char LETTER = 'A';
}

namespace AlertsSharedMem {
    const std::string SHMEM_FILE = "/bin/tar";
    const std::string LOCK_SHMEM_FILE = "/tmp/spawner_shm_lock";
    const char LETTER = 'C';
const size_t SHMEM_LENGTH = 1024;
}

namespace StampersSemaphore {
    const std::string SEM_FILE = "/bin/cat";
    const char LETTER = 'Z';
}

namespace FugitivesFifo {
    const std::string FUGITIVES_FIFO_FILE = "/tmp/archivofifo";
    const std::string BOOTH_LOCK_FILE = "/tmp/archivolock";
    const std::string SEM_FILE = "/bin/echo";
    const char LETTER = 'Y';
}

namespace PeopleFifo {
    const std::string FIFO_FILE = "/tmp/spawnerfifo";
    const std::string BOOTH_LOCK_FILE = "/tmp/spawnerfifolock";
}

#endif //MIGRATION_OFFICE_FILENAMES_H
