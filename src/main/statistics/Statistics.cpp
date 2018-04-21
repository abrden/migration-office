#include "Statistics.h"
#include "FileNames.h"
#include "SignalHandler.h"

Statistics::Statistics(size_t booths_number, const bool debug, const std::string& log_file)
        : logger(debug, log_file), booths_number(booths_number),
          shm(StatisticsSharedMemory::STATS_FILE, StatisticsSharedMemory::LETTER),
          lock(StatisticsSharedMemory::LOCK_STATS_FILE),
          fifo(StatisticsSharedMemory::FIFO_FILE) {

    logger(STATISTICS) << "Welcome to Conculandia's Statistics Department!" << std::endl;

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
    initialize_data();
    send_initialized_data_confirmation();
}

void Statistics::initialize_data() {
    StatisticsData default_data = {0, 0, 0, 0};
    shm.write(default_data);
}

void Statistics::send_initialized_data_confirmation() {
    const bool ready = true;
    for(size_t i = 0; i < booths_number; i++) fifo.fifo_write(&ready, sizeof(bool));
}

StatisticsData Statistics::update_data() {
    lock.lock();
    StatisticsData temp_data = shm.read();
    lock.unlock();
    return temp_data;
}

void Statistics::start() {
    std::string line;
    std::cout << "Ask for statistics (allowed residents, detained residents, allowed foreigners, deported foreigners) or just exit." << std::endl;
    std::cout << "> ";
    std::getline(std::cin, line);
    while (sigint_handler.get_graceful_quit() == 0 && line != "exit") {
        if (line == "allowed residents") {
            std::cout << "Allowed residents: " << get_allowed_residents() << std::endl;
        } else if (line == "detained residents"){
            std::cout << "Detained residents: " << get_detained_residents() << std::endl;
        } else if (line == "allowed foreigners") {
            std::cout << "Allowed foreigners: " << get_allowed_foreigners() << std::endl;
        } else if (line == "deported foreigners") {
            std::cout << "Deported foreigners: " << get_deported_foreigners() << std::endl;
        } else {
            std::cout << "Invalid command, try again" << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, line);
    }
}

size_t Statistics::get_allowed_residents() {
    return update_data().allowed_residents;
}

size_t Statistics::get_detained_residents() {
    return update_data().detained_residents;
}

size_t Statistics::get_allowed_foreigners() {
    return update_data().allowed_foreigners;
}

size_t Statistics::get_deported_foreigners() {
    return update_data().deported_foreigners;
}

Statistics::~Statistics() {
    SignalHandler::destroy();
}
