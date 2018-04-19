#include "EnviromentInitializer.h"

static const std::string STATS_FILE = "/bin/ls";
static const std::string LOCK_STATS_FILE = "/tmp/statistics_shm_lock";
static const char LETTER = 'A';

EnviromentInitializer::EnviromentInitializer() : stats_shm(STATS_FILE, LETTER) {}

void EnviromentInitializer::initialize() {
    Data default_data = {0, 0, 0, 0};
    stats_shm.write(default_data);
}
