#include "MinisterOfSecurity.h"
#include "ConfigurationFileReader.h"
#include "FileNames.h"
#include "BoothsWithUnreadFugitives.h"

#include <fstream>

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path,
                                       const std::string& fugitives_file_path,
                                       const size_t booths_number,
                                       const std::vector<pid_t>& booths_ids,
                                       const bool debug,
                                       const std::string& log_file_path) : logger(debug, log_file_path),
                                                                           fugitives_fifo(FugitivesFifo::FUGITIVES_FIFO_FILE),
                                                                           booths_number(booths_number),
                                                                           alerts_spawner(logger,
                                                                                          alerts_file_path,
                                                                                          booths_number,
                                                                                          booths_ids) {

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
    send_alerts();
}

void MinisterOfSecurity::send_alerts() {
    alerts_spawner.run();
}

void MinisterOfSecurity::send_fugitives() {
    size_t n_fugitives = fugitives.size();

    for(size_t i = 0; i < booths_number; i++) {
        logger(MINISTER) << "Sending " << fugitives.size() << " fugitives ids for booth " << i + 1 << std::endl;
        fugitives_fifo.fifo_write(static_cast<void*>(&n_fugitives), sizeof(size_t));
        if (n_fugitives > 0)
            fugitives_fifo.fifo_write(static_cast<void*>(fugitives.data()), sizeof(unsigned int) * fugitives.size());
    }

    logger(MINISTER) << "Waiting for booths read confirmations" << std::endl;
    booths.wait_for_booths_to_read();
    logger(MINISTER) << "Received all read confirmations" << std::endl;
}

MinisterOfSecurity::~MinisterOfSecurity() = default;
