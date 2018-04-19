#include "Statistics.h"

static const std::string STATS_FILE = "/bin/ls";
static const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
static const char LETTER = 'A';

Statistics::Statistics() : stats_shm(STATS_FILE, LETTER), stats_shm_lock(LOCK_STATS_FILE) {
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
