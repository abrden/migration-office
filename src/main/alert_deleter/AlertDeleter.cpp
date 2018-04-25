#include <src/main/common/definitions/AlertData.h>
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
    AlertData data;
    data.id = 0;

    alerts_shmem_lock.lock();
    size_t id = std::hash<std::string>{}(spawnable) % BUFFSIZE;
    size_t i = 0;
    AlertData read_data = alerts_shm.read(i);
    while (read_data.id != id) {
        read_data = alerts_shm.read(i++);
    }
    alerts_shm.write(id, data);
    alerts_shmem_lock.unlock();
}

AlertDeleter::~AlertDeleter() {
    SignalHandler::destroy();
}
