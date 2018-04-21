#include "StatisticsCommunicator.h"
#include "FileNames.h"

StatisticsCommunicator::StatisticsCommunicator() :
        shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER),
        lock(StatisticsSharedMemory::LOCK_STATS_FILE),
        fifo(StatisticsSharedMemory::FIFO_FILE),
        cnf_fifo(StatisticsSharedMemory::CNF_FIFO_FILE) {
    wait_for_initialization();
}

void StatisticsCommunicator::wait_for_initialization() {
    lock.lock();
    bool ready;
    fifo.fifo_read(static_cast<void*>(&ready), sizeof(bool));
    cnf_fifo.fifo_write(static_cast<void*>(&ready), sizeof(bool));
    lock.unlock();
}

void StatisticsCommunicator::increment_field(size_t field) {
    lock.lock();

    StatisticsData data = shm.read();
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
    shm.write(data);

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
