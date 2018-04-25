#include <src/main/common/definitions/AlertData.h>
#include "AlertDeleter.h"
#include "AlertData.h"
#include "FileNames.h"
#include "SignalHandler.h"

AlertDeleter::AlertDeleter(const std::string& alerts_file, const bool debug, const std::string& log_file)
        : Spawner(logger, alerts), logger(debug, log_file),
          alerts_shm(Alerts::SHMEM_FILE, Alerts::LETTER, Alerts::SHMEM_LENGTH),
          alerts_shmem_lock(Alerts::LOCK_SHMEM_FILE) {
    ConfigurationFileReader::load_alerts_deletion(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void AlertDeleter::spawn(std::string spawnable) {
    AlertData data;
    data.id = 0;

    alerts_shmem_lock.lock();

    size_t id = std::hash<std::string>{}(spawnable) % BUFFSIZE;
    logger(ALERT_DELETER) << "Searching for alert with id " << id  << " to be deleted." << std::endl;

    size_t i = 0;
    AlertData read_data = alerts_shm.read(i);
    while (read_data.id != id) {
        read_data = alerts_shm.read(i++);
    }

    logger(ALERT_DELETER) << "Alert with id " << id << " found, deleting." << std::endl;
    alerts_shm.write(id, data);
    logger(ALERT_DELETER) << "Alert with id " << id << " deleted." << std::endl;

    alerts_shmem_lock.unlock();
}

bool AlertDeleter::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertDeleter::~AlertDeleter() {
    SignalHandler::destroy();
}
