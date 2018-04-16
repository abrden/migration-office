#include <iostream>

#include "SharedLock.h"
#include "Police.h"

// TODO review this
static const char FILE_NAME[] = "/tmp/archivofifo";
static const char LOCK_FILE[] = "/tmp/archivolock";

Police::Police() : fifo(FILE_NAME) {
    fifo.fifo_open();
    std::cout << "opened fifo" << std::endl;
    unsigned long n_fugitives;
    fifo.fifo_read(static_cast<void*>(&n_fugitives), sizeof(unsigned long));
    std::cout << "I'm the prestigious Policia Bonaerense, I received " << n_fugitives << " fugitives ids" << std::endl;
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

