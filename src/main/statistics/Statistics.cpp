#include <iostream>
#include "Statistics.h"
#include "StatisticsData.h"
#include "FileNames.h"
#include "SignalHandler.h"

Statistics::Statistics(size_t booths_number, const bool debug, const std::string& log_file)
        : logger(debug, log_file), booths_number(booths_number),
          shm(StatisticsSharedMem::STATS_FILE, StatisticsSharedMem::LETTER, STATS_SIZE),
          lock(StatisticsSharedMem::LOCK_STATS_FILE) {

    logger(STATISTICS) << "Welcome to Conculandia's Statistics Department!" << std::endl;

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

size_t Statistics::get_field(size_t pos) {
    lock.lock();
    size_t* temp_data = shm.read();
    lock.unlock();
    return temp_data[pos];
}

void Statistics::start() {
    std::string line;
    std::cout << "Ask for statistics (allowed residents, detained residents, allowed foreigners, deported foreigners) or just exit." << std::endl;
    std::cout << "> ";
    std::getline(std::cin, line);
    while (sigint_handler.get_graceful_quit() == 0 && line != "exit") {
        if (line == "allowed residents") {
        std::cout << "Allowed residents: " << get_field(FIELDS::ALLOWED_RESIDENTS) << std::endl;
        } else if (line == "detained residents"){
            std::cout << "Detained residents: " << get_field(FIELDS::DETAINED_RESIDENTS) << std::endl;
        } else if (line == "allowed foreigners") {
            std::cout << "Allowed foreigners: " << get_field(FIELDS::ALLOWED_FOREIGNERS) << std::endl;
        } else if (line == "deported foreigners") {
            std::cout << "Deported foreigners: " << get_field(FIELDS::DEPORTED_FOREIGNERS) << std::endl;
        } else {
            std::cout << "Invalid command, try again" << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, line);
    }
}

Statistics::~Statistics() {
    SignalHandler::destroy();
}
