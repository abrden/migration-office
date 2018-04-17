#include <iostream>

#include "ExclusiveLock.h"
#include "Police.h"

// TODO review this
static const std::string FIFO_FILE = "/tmp/archivofifo";
static const std::string LOCK_FILE = "/tmp/archivolock";
static const size_t BUFFERSIZE = 2;

Police::Police() : fugitives_fifo(FIFO_FILE), fugitives_fifo_lock(LOCK_FILE) {
    receive_fugitives();
}

void Police::receive_fugitives() {

    size_t n_fugitives;
    fugitives_fifo_lock.lock();
    ssize_t read_1 = fugitives_fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(size_t));
    std::cout << "[MIGRATION BOOTH] Read: " << read_1 << std::endl;
    unsigned int fugi[BUFFERSIZE];
    ssize_t read_2 = fugitives_fifo.fifo_read(static_cast<void*>(fugi), sizeof(unsigned int) * n_fugitives);
    std::cout << "[MIGRATION BOOTH] Read: " << read_2 << std::endl;
    fugitives_fifo_lock.unlock();

    fugitives.assign(fugi, std::end(fugi));
    std::cout << "[MIGRATION BOOTH] Received " << n_fugitives << " fugitives ids" << std::endl;
    std::cout << "[MIGRATION BOOTH] First fugitive is: " << fugitives.at(0) << std::endl;
    std::cout << "[MIGRATION BOOTH] Second fugitive is: " << fugitives.at(1) << std::endl;
}

bool Police::is_fugitive(Resident* resident) {
    // TODO
    return false;
}

bool Police::is_wanted_person(Foreigner* foreigner) {
    // TODO
    return false;
}

void Police::report(Resident* resident) {
    // TODO
    std::cout << "Resident " << resident->get_id() << " you are arrested" << std::endl;
}

