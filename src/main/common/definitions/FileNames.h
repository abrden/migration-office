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

namespace Alerts {
    const std::string SHMEM_FILE = "/bin/tar";
    const std::string LOCK_SHMEM_FILE = "/tmp/spawner_shm_lock";
    const char LETTER = 'C';
    const std::string ACK_FIFO_FILE = "/tmp/alerts_ack_fifo";
    const size_t SHMEM_LENGTH = 1024;
}

namespace StampersSemaphore {
    const std::string SEM_FILE = "/bin/cat";
    const char LETTER = 'Z';
}

namespace FugitivesFifo {
    const std::string FUGITIVES_FIFO_FILE = "/tmp/archivofifo";
    const std::string BOOTH_FIFO_FILE = "/tmp/booth_fifo";
}

namespace PeopleFifo {
    const std::string FIFO_FILE = "/tmp/spawnerfifo";
}

#endif //MIGRATION_OFFICE_FILENAMES_H
