#include "EnviromentInitializer.h"
#include "FileNames.h"

EnviromentInitializer::EnviromentInitializer() :
        stats_shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER) {}

void EnviromentInitializer::initialize() {
    Data default_data = {0, 0, 0, 0};
    stats_shm.write(default_data);
}
