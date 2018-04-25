#include "AlertDeleter.h"
#include "AlertData.h"
#include "FileNames.h"
#include "SignalHandler.h"

AlertDeleter::AlertDeleter(Logger& logger, const std::string& alerts_file)
        : Spawner(logger, alerts), logger(logger),
          alerts_shm(Alerts::SHMEM_FILE, Alerts::LETTER, Alerts::SHMEM_LENGTH),
          alerts_shmem_lock(Alerts::LOCK_SHMEM_FILE) {
    ConfigurationFileReader::load_alerts_deletion(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void AlertDeleter::spawn(std::string spawnable) {
    AlertData data = {.id = 0};

    alerts_shmem_lock.lock();
    size_t pos = std::hash<std::string>{}(spawnable) % BUFFSIZE;
    alerts_shm.write(pos, data);
    alerts_shmem_lock.unlock();
}

AlertDeleter::~AlertDeleter() {
    SignalHandler::destroy();
}
