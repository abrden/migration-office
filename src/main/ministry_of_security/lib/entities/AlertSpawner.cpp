#include "AlertData.h"
#include "FifoReader.h"
#include "FileNames.h"
#include "AlertSpawner.h"
#include "SignalHandler.h"
#include "ConfigurationFileReader.h"

static size_t spawned_alerts = 1;

AlertSpawner::AlertSpawner(Logger& logger, const std::string& alerts_file, const size_t booths_number,
                           const std::vector<pid_t>& booths_ids)
        : Spawner(logger, alerts), logger(logger),
          alerts_shm(AlertsSharedMem::SHMEM_FILE, AlertsSharedMem::LETTER, AlertsSharedMem::SHMEM_LENGTH),
          alerts_shmem_lock(AlertsSharedMem::LOCK_SHMEM_FILE),
          booths_number(booths_number), booths_ids(booths_ids) {

    ConfigurationFileReader::load_spawnables(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

size_t AlertSpawner::find_new_alert_index() {
    // Callee did the lock
    size_t i;
    for (i = 0; i < AlertsSharedMem::SHMEM_LENGTH; i++) {
        AlertData alert = alerts_shm.read(i);
        if (alert.read_by_quantity == booths_number || alert.id == 0) break;
    }
    return i;
}

void AlertSpawner::spawn(std::string spawnable) {
    AlertData data;
    data.id = spawned_alerts++;
    size_t length = spawnable.copy(data.serialized_alert, spawnable.size(), 0);
    data.serialized_alert[length] = '\0';
    data.serialized_alert_size = spawnable.size();
    data.read_by_quantity = 0;

    alerts_shmem_lock.lock();
    logger(MINISTER) << "Looking for index to write alert" << std::endl;
    size_t pos = find_new_alert_index();
    logger(MINISTER) << "Pos: " << pos << std::endl;
    alerts_shm.write(pos, data);
    alerts_shmem_lock.unlock();
}

bool AlertSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertSpawner::~AlertSpawner() {
    SignalHandler::destroy();
}
