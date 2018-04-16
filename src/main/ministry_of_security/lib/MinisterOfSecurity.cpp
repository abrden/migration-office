#include "MinisterOfSecurity.h"
#include "ConfigurationFileReader.h"
#include "ExclusiveLock.h"

#include <fstream>
#include <sstream>
#include <iostream>

static const char FILE_NAME[] = "/tmp/archivofifo";
static const char LOCK_FILE[] = "/tmp/archivolock";

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path,
                                       const std::string& fugitives_file_path,
                                       const size_t booths_number) : fifo(FILE_NAME), booths_number(booths_number) {
    ConfigurationFileReader fr;
    fr.load_alerts(alerts_file_path, alerts);
    fr.load_fugitives_ids(fugitives_file_path, fugitives);
}

Spawnables& MinisterOfSecurity::get_alerts() {
    return alerts;
}

void MinisterOfSecurity::send_fugitives() {
    unsigned long n_fugitives = fugitives.size();
    fifo.fifo_open();

    for(size_t i = 0; i < booths_number; i++) {
        std::cout << "I'm the prestigious Pato Bullrich and I'm sending " << fugitives.size() << " fugitives!" << std::endl;
        fifo.fifo_write(static_cast<void*>(&n_fugitives), sizeof(unsigned long));
        fifo.fifo_write(static_cast<void*>(fugitives.data()), sizeof(unsigned int) * fugitives.size());
        std::cout << "Fugitives sent" << std::endl;
    }
}
