#include "Statistics.h"

static const std::string STATS_FILE = "/tmp/statistics_shm";
static const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
static const char LETTER = 'A';

enum FIELDS {
    ALLOWED_RESIDENTS,
    DETAINED_RESIDENTS,
    ALLOWED_FOREIGNERS,
    DEPORTED_FOREIGNERS
};

Statistics::Statistics() : stats_shm(STATS_FILE, LETTER), stats_shm_lock(LOCK_STATS_FILE) {
    data = {0, 0, 0, 0};
}


void Statistics::update_data() {
    stats_shm_lock.lock();
    size_t *temp_data= stats_shm.read();
    for(size_t i = 0; i < data.size(); i++) {
        data[i] = temp_data[i];
    }
    stats_shm_lock.unlock();
}

size_t Statistics::get_allowed_residents() {
    update_data();
    return data[FIELDS::ALLOWED_RESIDENTS];
}

size_t Statistics::get_detained_residents() {
    update_data();
    return data[FIELDS::DETAINED_RESIDENTS];
}

size_t Statistics::get_allowed_foreigners() {
    update_data();
    return data[FIELDS::ALLOWED_FOREIGNERS];
}

size_t Statistics::get_deported_foreigners() {
    update_data();
    return data[FIELDS::DEPORTED_FOREIGNERS];
}
