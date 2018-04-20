#include "Statistics.h"
#include "FileNames.h"

Statistics::Statistics() : stats_shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER),
                           stats_shm_lock(StatisticsSharedMemory::LOCK_STATS_FILE) {
    data = {0, 0, 0, 0};
}

void Statistics::update_data() {
    stats_shm_lock.lock();
    Data temp_data = stats_shm.read();
    data = temp_data;
    stats_shm_lock.unlock();
}

size_t Statistics::get_allowed_residents() {
    update_data();
    return data.allowed_residents;
}

size_t Statistics::get_detained_residents() {
    update_data();
    return data.detained_residents;
}

size_t Statistics::get_allowed_foreigners() {
    update_data();
    return data.allowed_foreigners;
}

size_t Statistics::get_deported_foreigners() {
    update_data();
    return data.deported_foreigners;
}
