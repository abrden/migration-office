#include "Statistics.h"
#include "FileNames.h"

Statistics::Statistics() : stats_shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER),
                           stats_shm_lock(StatisticsSharedMemory::LOCK_STATS_FILE) {}

Data Statistics::update_data() {
    stats_shm_lock.lock();
    Data temp_data = stats_shm.read();
    stats_shm_lock.unlock();
    return temp_data;
}

size_t Statistics::get_allowed_residents() {
    return update_data().allowed_residents;
}

size_t Statistics::get_detained_residents() {
    return update_data().detained_residents;
}

size_t Statistics::get_allowed_foreigners() {
    return update_data().allowed_foreigners;
}

size_t Statistics::get_deported_foreigners() {
    return update_data().deported_foreigners;
}
