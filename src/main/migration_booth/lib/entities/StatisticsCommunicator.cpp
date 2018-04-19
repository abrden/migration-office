#include "StatisticsCommunicator.h"

static const std::string STATS_FILE = "/tmp/statistics_shm";
static const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
static const char LETTER = 'A';

enum FIELDS {
    ALLOWED_RESIDENTS,
    DETAINED_RESIDENTS,
    ALLOWED_FOREIGNERS,
    DEPORTED_FOREIGNERS
};

StatisticsCommunicator::StatisticsCommunicator() : stats_shm(STATS_FILE, LETTER),
                                                   stats_shm_lock(LOCK_STATS_FILE) {}

void StatisticsCommunicator::increment_field(size_t field) {
    stats_shm_lock.lock();

    size_t *data = stats_shm.read();
    size_t new_data[4];
    data[field]++;
    *new_data = *data;
    stats_shm.write(new_data);

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
