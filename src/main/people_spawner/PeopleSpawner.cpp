#include <csignal>
#include <iostream>
#include "Person.h"
#include "SignalHandler.h"
#include "ConfigurationFileReader.h"
#include "PeopleSpawner.h"
#include "FileNames.h"

PeopleSpawner::PeopleSpawner(const std::string& people_file, const bool debug, const std::string& log_file)
        : Spawner(logger, people), logger(debug, log_file), fifo(PeopleFifo::FIFO_FILE) {

    logger(PEOPLE_SPAWNER) << "Welcome to the Conculandia Migration Spawner!" << std::endl;
    logger(PEOPLE_SPAWNER) << "people file = " << people_file << std::endl;
    logger(PEOPLE_SPAWNER) << "debug = " << debug << std::endl;
    logger(PEOPLE_SPAWNER) << "log file = " << log_file << std::endl;

    ConfigurationFileReader::load_persons(people_file, people);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void PeopleSpawner::spawn(std::string serialized_person) {
    unsigned long serialization_length = serialized_person.size();
    logger(PEOPLE_SPAWNER) << "Spawning person: " << serialized_person << ". with size: " << serialization_length << std::endl;

    // No need for locks, I'm the single writer of this fifo
    fifo.fifo_write(&serialization_length, sizeof(unsigned long));
    ssize_t bytes_sent = fifo.fifo_write(serialized_person.c_str(), sizeof(char) * serialization_length);
    logger(PEOPLE_SPAWNER) << "I sent " << bytes_sent << " bytes to the queue" << std::endl;
}

bool PeopleSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

PeopleSpawner::~PeopleSpawner() {
    SignalHandler::destroy();
    fifo.fifo_close();
}