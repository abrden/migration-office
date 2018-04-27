#include <csignal>
#include <iostream>
#include "Person.h"
#include "SignalHandler.h"
#include "ConfigurationFileReader.h"
#include "PeopleSpawner.h"
#include "FileNames.h"

PeopleSpawner::PeopleSpawner(const std::string& people_file, const bool debug, const std::string& log_file)
        : Spawner(logger, people), people_file(people_file), debug(debug), log_file(log_file), logger(debug, log_file), fifo(PeopleFifo::FIFO_FILE) {

    logger(PEOPLE_SPAWNER) << "Welcome to the Conculandia Migration Spawner!" << std::endl;
    logger(PEOPLE_SPAWNER) << "people file = " << people_file << std::endl;
    logger(PEOPLE_SPAWNER) << "debug = " << debug << std::endl;
    logger(PEOPLE_SPAWNER) << "log file = " << log_file << std::endl;

    ConfigurationFileReader::load_spawnables(people_file, people);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void PeopleSpawner::spawn(std::string serialized_person) {
    logger(PEOPLE_SPAWNER) << "Serialized person " << serialized_person << std::endl;

    unsigned long serialization_length = serialized_person.size();
    logger(PEOPLE_SPAWNER) << "The length is " << serialization_length << std::endl;

    fifo.fifo_write(&serialization_length, sizeof(unsigned long));
    ssize_t bytes_sent = fifo.fifo_write(serialized_person.c_str(), sizeof(char) * serialization_length);
    logger(PEOPLE_SPAWNER) << "I sent " << bytes_sent << " bytes" << std::endl;
}

bool PeopleSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

PeopleSpawner::~PeopleSpawner() {
    SignalHandler::destroy();
    fifo.fifo_close();
}