#include "MinisterOfSecurity.h"
#include "ConfigurationFileReader.h"
#include "ExclusiveLock.h"
#include "SignalHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

static const std::string FIFO_FILE = "/tmp/archivofifo";

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path,
                                       const std::string& fugitives_file_path,
                                       const size_t booths_number) : fifo(FIFO_FILE), booths_number(booths_number) {
    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
    ConfigurationFileReader fr;
    fr.load_alerts(alerts_file_path, alerts);
    fr.load_fugitives_ids(fugitives_file_path, fugitives);
}

void MinisterOfSecurity::open() {
    send_fugitives();
    while (sigint_handler.get_graceful_quit() == 0) {
        send_alerts();
        sleep(2); // FIXME sleepy sleep to avoid killing my cpu
    }
}

void MinisterOfSecurity::send_alerts() {
    std::cout << "Pato Bullrich sending high speed alerts!!" << std::endl;
    return; // FIXME implement
}

void MinisterOfSecurity::send_fugitives() {
    size_t n_fugitives = fugitives.size();

    for(size_t i = 0; i < booths_number; i++) {
        std::cout << "I'm the prestigious Pato Bullrich and I'm sending " << fugitives.size() << " fugitives!" << std::endl;
        fifo.fifo_write(static_cast<void*>(&n_fugitives), sizeof(size_t));
        fifo.fifo_write(static_cast<void*>(fugitives.data()), sizeof(unsigned int) * fugitives.size());
        std::cout << "Fugitives sent" << std::endl;
    }
}


MinisterOfSecurity::~MinisterOfSecurity() {
    SignalHandler::destroy();
}
