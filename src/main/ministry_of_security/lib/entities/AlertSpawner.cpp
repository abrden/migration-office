#include "AlertData.h"
#include "FifoReader.h"
#include "FileNames.h"
#include "AlertSpawner.h"
#include "SignalHandler.h"

static size_t spawned_alerts = 1;

AlertSpawner::AlertSpawner(Logger& logger, const std::string& alerts_file, const size_t booths_number,
                           const std::vector<pid_t>& booths_ids)
        : Spawner(logger, alerts), logger(logger),
          alerts_shm(Alerts::SHMEM_FILE, Alerts::LETTER, Alerts::SHMEM_LENGTH),
          alerts_shmem_lock(Alerts::LOCK_SHMEM_FILE),
          booths_number(booths_number), booths_ids(booths_ids) {

    ConfigurationFileReader::load_spawnables(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

size_t AlertSpawner::find_new_alert_index() {
    // Callee did the lock
    size_t i;
    for (i = 0; i < Alerts::SHMEM_LENGTH; i++) {
        std::string serialized_alert = alerts_shm.read(i);

        size_t id, read_by_quantity;
        serialized_alert.copy((char*)&id, sizeof(size_t), 0);
        logger(MINISTER) << "find_new_alert_index ID: " << id << std::endl;
        serialized_alert.copy((char*)&read_by_quantity, sizeof(size_t), sizeof(size_t));
        logger(MINISTER) << "find_new_alert_index READ_BY: " << read_by_quantity << std::endl;

        if (read_by_quantity == booths_number || id == 0) break;

    }
    return i;

}

std::string serialized_alert_data(AlertData data) {
    std::string s;

    char* id_arr = (char*)&data.id;
    for (unsigned int i = 0; i < sizeof(data.id); ++i)
        s.push_back(id_arr[i]);

    char* read_by_arr = (char*)&data.read_by_quantity;
    for (unsigned int i = 0; i < sizeof(data.read_by_quantity); ++i)
        s.push_back(read_by_arr[i]);

    char* size_arr = (char*)&data.serialized_alert_size;
    for (unsigned int i = 0; i < sizeof(data.serialized_alert_size); ++i)
        s.push_back(size_arr[i]);

    s.append(data.serialized_alert);

    return s;
}

void AlertSpawner::spawn(std::string spawnable) {
    AlertData data;
    data.id = spawned_alerts++;
    size_t length = spawnable.copy(data.serialized_alert, spawnable.size(), 0);
    data.serialized_alert[length] = '\0';
    data.serialized_alert_size = spawnable.size();
    data.read_by_quantity = 0;

    std::string serialized_alert = serialized_alert_data(data);

    alerts_shmem_lock.lock();
    logger(MINISTER) << "Looking for index to write alert" << std::endl;
    size_t pos = find_new_alert_index();
    logger(MINISTER) << "Pos: " << pos << std::endl;
    alerts_shm.write(pos, serialized_alert);
    alerts_shmem_lock.unlock();
}

bool AlertSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertSpawner::~AlertSpawner() {
    SignalHandler::destroy();
}
