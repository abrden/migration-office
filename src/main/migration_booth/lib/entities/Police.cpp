#include <iostream>

#include "ExclusiveLock.h"
#include "Police.h"

// TODO review this
static const char FILE_NAME[] = "/tmp/archivofifo";
static const char LOCK_FILE[] = "/tmp/archivolock";
static const size_t BUFFERSIZE = 2;

Police::Police() : fugitives_fifo(FILE_NAME), fugitives_fifo_lock(LOCK_FILE) {
    receive_fugitives();
}

void Police::receive_fugitives() {

    size_t n_fugitives;
    fugitives_fifo_lock.lock();
    ssize_t read_1 = fugitives_fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(size_t));
    std::cout << "Read: " << read_1 << std::endl;
    unsigned int fugi[BUFFERSIZE];
    ssize_t read_2 = fugitives_fifo.fifo_read(static_cast<void*>(fugi), sizeof(unsigned int) * n_fugitives);
    std::cout << "Read: " << read_2 << std::endl;
    fugitives_fifo_lock.unlock();

    fugitives.assign(fugi, std::end(fugi));
    std::cout << "I'm the prestigious Policia Bonaerense, I received " << n_fugitives << " fugitives ids" << std::endl;
    std::cout << "First fugitive is: " << fugitives.at(0) << std::endl;
    std::cout << "Second fugitive is: " << fugitives.at(1) << std::endl;
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

