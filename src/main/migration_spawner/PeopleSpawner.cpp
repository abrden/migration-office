#include "ConfigurationFileReader.h"
#include "PeopleSpawner.h"

PeopleSpawner::PeopleSpawner(const std::string& people_file, const bool debug, const std::string& log_file)
        : people_file(people_file), debug(debug), log_file(log_file), spawner(people) {
    ConfigurationFileReader fr;
    fr.load_persons(people_file, people);
}

void PeopleSpawner::start() {
    spawner.run(); // TODO graceful quit
}

PeopleSpawner::~PeopleSpawner() = default;