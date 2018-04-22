#include <src/main/common/concurrency/FifoReader.h>
#include <src/main/common/definitions/AlertData.h>
#include "FileNames.h"
#include "AlertSpawner.h"

#include "SignalHandler.h"

AlertSpawner::AlertSpawner(Logger& logger, const std::string& alerts_file, const size_t booths_number)
        : Spawner(logger, alerts),
          logger(logger),
          shmem(AlertsSharedMemory::SHMEM_FILE, AlertsSharedMemory::LETTER),
          shmem_lock(AlertsSharedMemory::LOCK_SHMEM_FILE),
          booths_number(booths_number) {

    ConfigurationFileReader::load_spawnables(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void AlertSpawner::spawn(std::string spawnable) {
    shmem_lock.lock();
    AlertData data;
    size_t length = spawnable.copy(data.serialized_alert, spawnable.size(), 0);
    data.serialized_alert[length] = '\0';
    data.serialized_alert_size = spawnable.size();
    data.read_by_quantity = 0;
    shmem.write(data);
    shmem_lock.unlock();

    // TODO Send signal to booths

    FifoReader fifo(AlertsSharedMemory::ACK_FIFO_FILE);
    size_t ack, received_id;
    ack = 0;
    for (size_t i = 0; i < booths_number; i++) {
        fifo.fifo_read(static_cast<void*>(&received_id), sizeof(received_id));
        //TODO if (bytes_read != sizeof(received_id)) error
        if (received_id == data.id) ack++;
    }
}

bool AlertSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertSpawner::~AlertSpawner() {
    SignalHandler::destroy();
}