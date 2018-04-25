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

    size_t pos = 0;
    AlertData read_data = alerts_shm.read(pos);
    while (read_data.id != id && pos < BUFFSIZE) {
        read_data = alerts_shm.read(pos++);
    }

    if (pos == BUFFSIZE) {
        std::string message = "Error in alert deletion: alert with id " + std::to_string(id) + " not found.";
        throw std::runtime_error(message);
    }
    logger(ALERT_DELETER) << "Alert with id " << id << " found in position " << pos << ", deleting." << std::endl;
    alerts_shm.write(pos, data);
    logger(ALERT_DELETER) << "Alert with id " << id << " found in position " << pos << " deleted." << std::endl;

    alerts_shmem_lock.unlock();
}

bool AlertDeleter::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertDeleter::~AlertDeleter() {
    SignalHandler::destroy();
}
