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
    fugitives_fifo_lock.unlock();

    logger(BOOTH_POLICE) << "Read fugitives size: " << read_2 << std::endl;

    fugitives.assign(fugi, std::end(fugi));
    logger(BOOTH_POLICE) << "Received " << n_fugitives << " fugitives ids" << std::endl;

    logger(BOOTH_POLICE) << "Sending read confirmation" << std::endl;
    booths.notify_read_fugitives();
}

bool Police::is_new_alert(size_t id) {
    if (id == 0) return false;
    for (auto it = alerts.begin(); it != alerts.end(); ++it) {
        if ((*it)->get_id() == id) return false;
    }
    return true;
}

void Police::receive_alerts() {
    alerts_lock.lock();
    for (size_t i = 0; i < AlertsSharedMem::SHMEM_LENGTH; i++){
        AlertData alert_data = alerts_shm.read(i);

        if (is_new_alert(alert_data.id)) {
            logger(BOOTH_POLICE) << "receive_alerts ID: " << alert_data.id << std::endl;
            logger(BOOTH_POLICE) << "receive_alerts SIZE: " << alert_data.serialized_alert_size << std::endl;
            std::string alert_str(alert_data.serialized_alert, alert_data.serialized_alert_size);
            logger(BOOTH_POLICE) << "Received alert: " << alert_str << std::endl;

            WantedPersonAlert* alert = AlertDeserializer::deserialize(alert_str, alert_data.id);
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
