#include "StatisticsCommunicator.h"
#include "FileNames.h"

StatisticsCommunicator::StatisticsCommunicator() :
        stats_shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER),
        stats_shm_lock(StatisticsSharedMemory::LOCK_STATS_FILE) {}

void StatisticsCommunicator::increment_field(size_t field) {
    stats_shm_lock.lock();

    Data data = stats_shm.read();
    switch (field) {
        case FIELDS::ALLOWED_RESIDENTS:
            data.allowed_residents++;
            break;
        case FIELDS::DETAINED_RESIDENTS:
            data.detained_residents++;
            break;
        case FIELDS::ALLOWED_FOREIGNERS:
            data.allowed_foreigners++;
            break;
        case FIELDS::DEPORTED_FOREIGNERS:
            data.deported_foreigners++;
    }
    stats_shm.write(data);

    stats_shm_lock.unlock();
}

void StatisticsCommunicator::notify_allowed_resident() {
    increment_field(FIELDS::ALLOWED_RESIDENTS);
}

void StatisticsCommunicator::notify_detained_resident() {
    increment_field(FIELDS::DETAINED_RESIDENTS);
}

void StatisticsCommunicator::notify_allowed_foreigner() {
    increment_field(FIELDS::ALLOWED_FOREIGNERS);
}

void StatisticsCommunicator::notify_deported_foreigner() {
    increment_field(FIELDS::DEPORTED_FOREIGNERS);
}
