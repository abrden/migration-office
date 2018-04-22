#include "FileNames.h"
#include "AlertSpawner.h"

#include "SignalHandler.h"

AlertSpawner::AlertSpawner(Logger& logger, const std::string& alerts_file)
        : Spawner(logger, alerts),
          logger(logger),
          shmem(AlertsSharedMemory::SHMEM_FILE, AlertsSharedMemory::LETTER),
          shmem_lock(AlertsSharedMemory::LOCK_SHMEM_FILE) {

    ConfigurationFileReader::load_spawnables(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void AlertSpawner::spawn(std::string spawnable) {
    shmem_lock.lock();
    AlertData data;
    std::size_t length = spawnable.copy(data.serialized_alert, spawnable.size(), 0);
    data.serialized_alert[length]='\0';
    data.serialized_alert_size = spawnable.size();
    data.read_by_quantity = 0;
    shmem.write(data);
    shmem_lock.lock();

    // TODO Send signal to booths
}

bool AlertSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertSpawner::~AlertSpawner() {
    SignalHandler::destroy();
}