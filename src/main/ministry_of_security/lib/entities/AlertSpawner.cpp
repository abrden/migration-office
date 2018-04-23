#include "AlertData.h"
#include "FifoReader.h"
#include "AlertData.h"
#include "FileNames.h"
#include "AlertSpawner.h"
#include "SignalHandler.h"

#include <sys/types.h>
#include <signal.h>

static size_t spawned_alerts = 1;

AlertSpawner::AlertSpawner(Logger& logger, const std::string& alerts_file, const size_t booths_number,
                           const std::vector<pid_t>& booths_ids)
        : Spawner(logger, alerts), logger(logger),
          alerts_shm_arr(AlertsSharedMemory::SHMEM_FILE, AlertsSharedMemory::LETTER, AlertsSharedMemory::SHMEM_SIZE),
          shmem_lock(AlertsSharedMemory::LOCK_SHMEM_FILE),
          booths_number(booths_number), booths_ids(booths_ids) {

    ConfigurationFileReader::load_spawnables(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

size_t AlertSpawner::find_new_alert_index() {
    AlertData* data = alerts_shm_arr.read();
    size_t i;
    // TODO check what happens when memory is full
    for (i = 0; i < AlertsSharedMemory::SHMEM_SIZE && data[i].read_by_quantity < booths_number && data[i].id != 0; i++);
    return i;
}

void AlertSpawner::spawn(std::string spawnable) {
    AlertData data;
    data.id = spawned_alerts++;
    size_t length = spawnable.copy(data.serialized_alert, spawnable.size(), 0);
    data.serialized_alert[length] = '\0';
    data.serialized_alert_size = spawnable.size();
    data.read_by_quantity = 0;

    shmem_lock.lock();
    size_t pos = find_new_alert_index();
    logger(MINISTER) << "Pos: " << pos << std::endl;
    alerts_shm_arr.write(pos, data);
    shmem_lock.unlock();
}

bool AlertSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertSpawner::~AlertSpawner() {
    SignalHandler::destroy();
}
