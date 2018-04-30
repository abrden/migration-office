#include "AlertData.h"
#include "FileNames.h"
#include "AlertData.h"
#include "AlertDeserializer.h"
#include "ExclusiveLock.h"
#include "Police.h"
#include "FileNames.h"
#include "BoothsWithUnreadFugitives.h"

#include <algorithm>
#include <iostream>

static const size_t BUFFERSIZE = 100;

Police::Police(Logger& logger)
        : logger(logger), fugitives_fifo(FugitivesFifo::FUGITIVES_FIFO_FILE),
          fugitives_fifo_lock(FugitivesFifo::BOOTH_LOCK_FILE),
          alerts_lock(AlertsSharedMem::LOCK_SHMEM_FILE),
          alerts_shm(AlertsSharedMem::SHMEM_FILE, AlertsSharedMem::LETTER, AlertsSharedMem::SHMEM_LENGTH) {
}

void Police::receive_fugitives() {
    fugitives_fifo_lock.lock();
    logger(BOOTH_POLICE) << "Reading fugitives ids" << std::endl;
    size_t n_fugitives;
    ssize_t size_bytes_read = fugitives_fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(size_t));
    if (size_bytes_read == 0) {
        logger(BOOTH_POLICE) << "No fugitives size to read" << std::endl;
    } else if ((unsigned long) size_bytes_read < sizeof(size_t)) {
        fugitives_fifo_lock.unlock();
        throw std::runtime_error("Failed to read size_t");
    }

    if (size_bytes_read > 0 && n_fugitives > 0) {
        unsigned int ids_buffer[BUFFERSIZE];
        ssize_t buffer_bytes_read = fugitives_fifo.fifo_read(static_cast<void*>(ids_buffer), sizeof(unsigned int) * n_fugitives);
        if (buffer_bytes_read == 0) {
            logger(BOOTH_POLICE) << "No fugitives ids to read" << std::endl;
        } else if ((unsigned long) buffer_bytes_read < sizeof(unsigned int) * n_fugitives) {
            fugitives_fifo_lock.unlock();
            throw std::runtime_error("Failed to read fugitives ids buffer");
        } else {
            fugitives.assign(ids_buffer, std::end(ids_buffer));
        }
    }
    fugitives_fifo_lock.unlock();

    logger(BOOTH_POLICE) << "Received " << n_fugitives << " fugitives ids. Sending read confirmation" << std::endl;
    booths.notify_read_fugitives();
}

void Police::get_current_alerts() {
    alerts.clear();
    alerts_lock.lock();
    for (size_t i = 0; i < AlertsSharedMem::SHMEM_LENGTH; i++){
        AlertData alert_data = alerts_shm.read(i);

        if (alert_data.id > 0) {
            std::string alert_str(alert_data.serialized_alert, alert_data.serialized_alert_size);
            logger(BOOTH_POLICE) << "Loading alert with ID: " << alert_data.id << ", size: "
                                 << alert_data.serialized_alert_size << ", and content: " << alert_str << std::endl;

            WantedPersonAlert *alert = AlertDeserializer::deserialize(alert_str, alert_data.id);
            alerts.emplace_back(alert);
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

Police::~Police() {
    while (!alerts.empty()) {
        delete alerts.back();
        alerts.pop_back();
    }
}
