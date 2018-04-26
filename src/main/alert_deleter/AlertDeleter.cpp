#include "AlertData.h"
#include "AlertDeleter.h"
#include "AlertData.h"
#include "FileNames.h"
#include "SignalHandler.h"
#include "ConfigurationFileReader.h"

#include <stdexcept>

AlertDeleter::AlertDeleter(const std::string& alerts_file, const bool debug, const std::string& log_file)
        : Spawner(logger, alerts), logger(debug, log_file),
          alerts_shm(Alerts::SHMEM_FILE, Alerts::LETTER, Alerts::SHMEM_LENGTH),
          alerts_shmem_lock(Alerts::LOCK_SHMEM_FILE) {
    ConfigurationFileReader::load_alerts_deletion(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void AlertDeleter::spawn(std::string spawnable) {
    AlertData data = {0, 0, '\0'};

    alerts_shmem_lock.lock();

    logger(ALERT_DELETER) << "Alert to delete: " << spawnable << std::endl;
    size_t id = std::hash<std::string>{}(spawnable) % BUFFSIZE;
    logger(ALERT_DELETER) << "Searching for alert with id " << id  << " to be deleted." << std::endl;

    size_t  pos;
    for (pos = 0; pos < Alerts::SHMEM_LENGTH; pos++) {
        AlertData alert = alerts_shm.read(pos);
        if (alert.id == id) break;
    }

    // FIXME not sure about throwing this exception or what to do in this case
    if (pos == Alerts::SHMEM_LENGTH) {
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
