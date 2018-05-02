#include "StatisticsCommunicator.h"
#include "FileNames.h"
#include "StatisticsData.h"

StatisticsCommunicator::StatisticsCommunicator() :
        shm(StatisticsSharedMem::STATS_FILE, StatisticsSharedMem::LETTER, STATS_SIZE),
        lock(StatisticsSharedMem::LOCK_STATS_FILE) {}

void StatisticsCommunicator::increment_field(size_t pos) {
    lock.lock();

    size_t* data = shm.read();
    shm.write(pos, ++data[pos]);

    lock.unlock();
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
