#include <csignal>
#include <iostream>
#include "Person.h"
#include "PersonSerializer.h"
#include "SignalHandler.h"
#include "ConfigurationFileReader.h"
#include "PeopleSpawner.h"

static const std::string FIFO_FILE = "/tmp/spawnerfifo";

PeopleSpawner::PeopleSpawner(const std::string& people_file, const bool debug, const std::string& log_file)
        : Spawner(people), people_file(people_file), debug(debug), log_file(log_file), fifo(FIFO_FILE) {

    ConfigurationFileReader fr;
    fr.load_spawnables(people_file, people);

    fifo.fifo_open();

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}


void PeopleSpawner::spawn(std::string serialized_person) {
    //std::string serialized_person = PersonSerializer::serialize((Person*)spawnable); // TODO dont use persons on this side
    std::cout << "Serialized person " << serialized_person << std::endl;

    unsigned long serialization_length = serialized_person.size();
    std::cout << "[PEOPLE SPAWNER] The length is " << serialization_length << std::endl;

    fifo.fifo_write(&serialization_length, sizeof(unsigned long));
    ssize_t bytes_sent = fifo.fifo_write(serialized_person.c_str(), sizeof(char) * serialization_length);
    std::cout << "[PEOPLE SPAWNER] I sent " << bytes_sent << " bytes" << std::endl;
}

bool PeopleSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

PeopleSpawner::~PeopleSpawner() {
    SignalHandler::destroy();
    fifo.fifo_close();
}