#include "MinisterOfSecurity.h"
#include "ConfigurationFileReader.h"

#include <fstream>
#include <iostream>

static const std::string FUGITIVES_FIFO_FILE = "/tmp/archivofifo";
static const std::string BOOTH_FIFO_FILE = "/tmp/booth_fifo";

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path,
                                       const std::string& fugitives_file_path,
                                       const size_t booths_number,
                                       const bool debug,
                                       const std::string& log_file_path) : logger(debug, log_file_path),
                                                                           fugitives_fifo(FUGITIVES_FIFO_FILE),
                                                                           booths_fifo(BOOTH_FIFO_FILE),
                                                                           booths_number(booths_number),
                                                                           alerts_spawner(logger, alerts_file_path) {

    logger(MINISTER) << "Welcome to the Conculandia Ministry of Security!" << std::endl;
    logger(MINISTER) << "alerts file = " << alerts_file_path << std::endl;
    logger(MINISTER) << "fugitives file = " << fugitives_file_path << std::endl;
    logger(MINISTER) << "debug = " << debug << std::endl;
    logger(MINISTER) << "log file = " << log_file_path << std::endl;
    logger(MINISTER) << "booths_number = " << booths_number << std::endl;

    ConfigurationFileReader::load_fugitives_ids(fugitives_file_path, fugitives);
}

void MinisterOfSecurity::open() {
    send_fugitives();
    receive_confirmations();
}

void MinisterOfSecurity::send_alerts() {
    logger(MINISTER) << "Pato Bullrich sending high speed alerts!" << std::endl;
    alerts_spawner.run();
}

void MinisterOfSecurity::send_fugitives() {
    size_t n_fugitives = fugitives.size();

    for(size_t i = 0; i < booths_number; i++) {
        logger(MINISTER) << "Sending " << fugitives.size() << " fugitives!" << std::endl;
        fugitives_fifo.fifo_write(static_cast<void*>(&n_fugitives), sizeof(size_t));
        fugitives_fifo.fifo_write(static_cast<void*>(fugitives.data()), sizeof(unsigned int) * fugitives.size());
        logger(MINISTER) << "Fugitives sent" << std::endl;
    }
}


void MinisterOfSecurity::receive_confirmations() {
    for(size_t i = 0; i < booths_number; i++) {
        logger(MINISTER) << "I'm receiving message confirmation number " << i << std::endl;
        bool confirmation;
        booths_fifo.fifo_read(static_cast<void*>(&confirmation), sizeof(bool));
        logger(MINISTER) << "Received confirmation!" << std::endl;
    }
}

MinisterOfSecurity::~MinisterOfSecurity() = default;
