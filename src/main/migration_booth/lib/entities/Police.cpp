#include "AlertData.h"
#include "FileNames.h"
#include "AlertData.h"
#include "SharedMemory.h"
#include "AlertDeserializer.h"
#include "ExclusiveLock.h"
#include "Police.h"

#include <iostream>
#include <algorithm>

static const std::string FIFO_FILE = "/tmp/archivofifo";
static const std::string BOOTH_FIFO_FILE = "/tmp/booth_fifo";
static const std::string LOCK_FILE = "/tmp/archivolock";
static const size_t BUFFERSIZE = 100;

Police::Police(Logger& logger)
        : logger(logger), fugitives_fifo(FIFO_FILE), ministry_fifo(BOOTH_FIFO_FILE),
          fugitives_fifo_lock(LOCK_FILE), alerts_lock(Alerts::LOCK_SHMEM_FILE),
          alerts_shm(Alerts::SHMEM_FILE, Alerts::LETTER, Alerts::SHMEM_LENGTH) {
}

void Police::receive_fugitives() {
    logger(BOOTH_POLICE) << "Locking..." << std::endl;
    fugitives_fifo_lock.lock();
    size_t n_fugitives;
    logger(BOOTH_POLICE) << "Reading..." << std::endl;
    ssize_t read_1 = fugitives_fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(size_t));
    logger(BOOTH_POLICE) << "Read size: " << read_1 << std::endl;
    if (read_1 <= 0) {
        std::cout << "[MIGRATION BOOTH] Invalid read, closing.." << std::endl;
        return;
    }
    unsigned int fugi[BUFFERSIZE];
    ssize_t read_2 = fugitives_fifo.fifo_read(static_cast<void*>(fugi), sizeof(unsigned int) * n_fugitives);
    logger(BOOTH_POLICE) << "Read fugitives size: " << read_2 << std::endl;

    fugitives.assign(fugi, std::end(fugi));
    logger(BOOTH_POLICE) << "Received " << n_fugitives << " fugitives ids" << std::endl;

    logger(BOOTH_POLICE) << "Sending read confirmation" << std::endl;
    bool confirmation = true;
    ministry_fifo.fifo_write(static_cast<void*>(&confirmation), sizeof(bool));
    fugitives_fifo_lock.unlock();
}

void Police::receive_alerts() {
    alerts_lock.lock();
    for (size_t i = 0; i < Alerts::SHMEM_LENGTH; i++){
        std::string serialized_alert = alerts_shm.read(i);

        size_t id, read_by_quantity, size;
        serialized_alert.copy((char*)&id, sizeof(size_t), 0);
        serialized_alert.copy((char*)&read_by_quantity, sizeof(size_t), sizeof(size_t));
        serialized_alert.copy((char*)&size, sizeof(size_t), 2 * sizeof(size_t));

        if (is_new_alert(id)) {
            logger(BOOTH_POLICE) << "receive_alerts ID: " << id << std::endl;
            logger(BOOTH_POLICE) << "receive_alerts READ_BY: " << read_by_quantity << std::endl;
            logger(BOOTH_POLICE) << "receive_alerts SIZE: " << size << std::endl;
            std::string alert_str = serialized_alert.substr(3 * sizeof(size_t), size);
            logger(BOOTH_POLICE) << "Received alert: " << alert_str << std::endl;
            WantedPersonAlert* alert = AlertDeserializer::deserialize(alert_str, id);
            alerts.emplace_back(alert);
            // FIXME data.read_by_quantity++;
            // FIXME alerts_shm.write(i, data);
        }
    }
    alerts_lock.unlock();
}

bool Police::is_fugitive(Resident* resident) {
    return std::find(fugitives.begin(), fugitives.end(), resident->get_id()) != fugitives.end();
}

bool Police::is_wanted_person(Foreigner* foreigner) {
    for (auto it = alerts.begin(); it != alerts.end(); ++it) {
        if ((*it)->get_features() == foreigner->get_features()) return true;
    }
    return false;
}

void Police::report(Resident* resident) {
    logger(BOOTH_POLICE) << "Resident " << resident->get_id() << " you are arrested" << std::endl;
    arrested_residents++;
}

void Police::report(Foreigner* foreigner) {
    logger(BOOTH_POLICE) << "Foreigner " << foreigner->get_passport().get_id() << " you are deported" << std::endl;
    deported_foreigners++;
}

bool Police::is_new_alert(size_t id) {
    if (id == 0) return false;
    for (auto it = alerts.begin(); it != alerts.end(); ++it) {
        if ((*it)->get_id() == id) return false;
    }
    return true;
}

Police::~Police() {
    while (!alerts.empty()) {
        delete alerts.back();
        alerts.pop_back();
    }
}
