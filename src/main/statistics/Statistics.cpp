#include <iostream>
#include "Statistics.h"
#include "StatisticsData.h"
#include "FileNames.h"
#include "SignalHandler.h"

Statistics::Statistics(const bool debug, const std::string& log_file)
        : logger(debug, log_file),
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
            size_t ans = get_field(FIELDS::ALLOWED_RESIDENTS);
            logger(STATISTICS) << "Answering 'allowed residents' query with: " << ans << std::endl;
            std::cout << "Allowed residents: " << ans << std::endl;
        } else if (line == "detained residents"){
            size_t ans = get_field(FIELDS::DETAINED_RESIDENTS);
            logger(STATISTICS) << "Answering 'detained residents' query with: " << ans << std::endl;
            std::cout << "Detained residents: " << ans << std::endl;
        } else if (line == "allowed foreigners") {
            size_t ans = get_field(FIELDS::ALLOWED_FOREIGNERS);
            logger(STATISTICS) << "Answering 'allowed foreigners' query with: " << ans << std::endl;
            std::cout << "Allowed foreigners: " << ans << std::endl;
        } else if (line == "deported foreigners") {
            size_t ans = get_field(FIELDS::DEPORTED_FOREIGNERS);
            logger(STATISTICS) << "Answering 'deported foreigners' query with: " << ans << std::endl;
            std::cout << "Deported foreigners: " << ans << std::endl;
        } else {
            logger(STATISTICS) << "Invalid query received: " << line  << std::endl;
            std::cout << "Invalid query, try again" << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, line);
    }
}

Statistics::~Statistics() {
    SignalHandler::destroy();
}
