#include "Statistics.h"
#include "FileNames.h"

Statistics::Statistics(size_t booths_number) : booths_number(booths_number),
                                               stats_shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER),
                                               stats_shm_lock(StatisticsSharedMemory::LOCK_STATS_FILE),
                                               fifo(StatisticsSharedMemory::FIFO_FILE) {
    initialize_data();
    send_initialized_data_confirmation();
}

void Statistics::initialize_data() {
    StatisticsData default_data = {0, 0, 0, 0};
    stats_shm.write(default_data);
}

void Statistics::send_initialized_data_confirmation() {
    const bool ready = true;
    for(size_t i = 0; i < booths_number; i++) fifo.fifo_write(&ready, sizeof(bool));
}

StatisticsData Statistics::update_data() {
    stats_shm_lock.lock();
    StatisticsData temp_data = stats_shm.read();
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
