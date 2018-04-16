#include <iostream>

#include "ExclusiveLock.h"
#include "Police.h"

// TODO review this
static const char FILE_NAME[] = "/tmp/archivofifo";
static const char LOCK_FILE[] = "/tmp/archivolock";
static const size_t BUFFERSIZE = 2;

Police::Police() : fifo(FILE_NAME) {
    std::cout << "Creating lock" << std::endl;
    ExclusiveLock lock(LOCK_FILE);
    fifo.fifo_open();
    std::cout << "opened fifo" << std::endl;
    unsigned long n_fugitives;
    lock.lock();
    ssize_t read_1 = fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(unsigned long));
    std::cout << "Read: " << read_1 << std::endl;
    unsigned int fugi[BUFFERSIZE];
    ssize_t read_2 = fifo.fifo_read(static_cast<void*>(fugi), sizeof(unsigned int) * n_fugitives);
    std::cout << "Read: " << read_2 << std::endl;
    lock.unlock();
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

