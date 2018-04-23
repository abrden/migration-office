#include <iostream>
#include <algorithm>
#include "FileNames.h"
#include "AlertData.h"
#include "SharedMemory.h"
#include "AlertDeserializer.h"

#include "ExclusiveLock.h"
#include "Police.h"

static const std::string FIFO_FILE = "/tmp/archivofifo";
static const std::string BOOTH_FIFO_FILE = "/tmp/booth_fifo";
static const std::string LOCK_FILE = "/tmp/archivolock";
static const size_t BUFFERSIZE = 100;

Police::Police(Logger& logger) : logger(logger),
                                 fugitives_fifo(FIFO_FILE),
                                 ministry_fifo(BOOTH_FIFO_FILE),
                                 fugitives_fifo_lock(LOCK_FILE),
                                 alerts_lock(AlertsSharedMemory::LOCK_SHMEM_FILE),
                                 alerts_shm(AlertsSharedMemory::SHMEM_FILE, AlertsSharedMemory::LETTER),
                                 alerts_fifo(AlertsSharedMemory::ACK_FIFO_FILE) {
    receive_fugitives();
}

void Police::receive_fugitives() {
    fugitives_fifo_lock.lock();
    size_t n_fugitives;
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

void Police::receive_alert() {
    alerts_lock.lock();
    AlertData data = alerts_shm.read();
    alerts_lock.unlock();

    std::string serialized_alert(data.serialized_alert);
    WantedPersonAlert* alert = AlertDeserializer::deserialize(serialized_alert);
    alerts.emplace_back(alert);

    alerts_fifo.fifo_write(static_cast<void*>(&data.id), sizeof(data.id));
}

bool Police::is_fugitive(Resident* resident) {
    return std::find(fugitives.begin(), fugitives.end(), resident->get_id()) != fugitives.end();
}

bool Police::is_wanted_person(Foreigner* foreigner) {
    // TODO
    return false;
}

void Police::report(Resident* resident) {
    logger(BOOTH_POLICE) << "Resident " << resident->get_id() << " you are arrested" << std::endl;
    arrested_residents++;
    delete resident;
}

void Police::report(Foreigner* foreigner) {
    logger(BOOTH_POLICE) << "Foreigner " << foreigner->get_passport().get_id() << " you are deported" << std::endl;
    deported_foreigners++;
    delete foreigner;
}

