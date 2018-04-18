#include <iostream>
#include <algorithm>

#include "ExclusiveLock.h"
#include "Police.h"

// TODO review this
static const std::string FIFO_FILE = "/tmp/archivofifo";
static const std::string BOOTH_FIFO_FILE = "/tmp/booth_fifo";
static const std::string LOCK_FILE = "/tmp/archivolock";
static const size_t BUFFERSIZE = 2;

Police::Police() : fugitives_fifo(FIFO_FILE),
                   ministry_fifo(BOOTH_FIFO_FILE),
                   fugitives_fifo_lock(LOCK_FILE) {
    receive_fugitives();
}

void Police::receive_fugitives() {

    fugitives_fifo_lock.lock();
    size_t n_fugitives;
    ssize_t read_1 = fugitives_fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(size_t));
    std::cout << "[MIGRATION BOOTH] Read size: " << read_1 << std::endl;
    if (read_1 <= 0) {
        std::cout << "[MIGRATION BOOTH] Invalid read, closing.." << std::endl;
        return;
    }
    unsigned int fugi[BUFFERSIZE];
    ssize_t read_2 = fugitives_fifo.fifo_read(static_cast<void*>(fugi), sizeof(unsigned int) * n_fugitives);
    std::cout << "[MIGRATION BOOTH] Read fugitives size: " << read_2 << std::endl;

    fugitives.assign(fugi, std::end(fugi));
    std::cout << "[MIGRATION BOOTH] Received " << n_fugitives << " fugitives ids" << std::endl;
    std::cout << "[MIGRATION BOOTH] First fugitive is: " << fugitives.at(0) << std::endl;
    std::cout << "[MIGRATION BOOTH] Second fugitive is: " << fugitives.at(1) << std::endl;

    std::cout << "[MIGRATION BOOTH] Sending read confirmation" << std::endl;
    bool confirmation = true;
    ministry_fifo.fifo_write(static_cast<void*>(&confirmation), sizeof(bool));
    fugitives_fifo_lock.unlock();
}

bool Police::is_fugitive(Resident* resident) {
    return std::find(fugitives.begin(), fugitives.end(), resident->get_id()) != fugitives.end();
}

bool Police::is_wanted_person(Foreigner* foreigner) {
    // TODO
    return false;
}

void Police::report(Resident* resident) {
    // TODO
    std::cout << "[POLICE] Resident " << resident->get_id() << " you are arrested" << std::endl;
    delete resident;
}

