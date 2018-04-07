#include "PersonsGenerator.h"
#include "src/main/common/ConfigurationFileReader.h"

PersonsGenerator::PersonsGenerator(const std::string& persons_file_path) {
    ConfigurationFileReader fr;
    fr.load_persons(persons_file_path, persons);
}

Spawnables& PersonsGenerator::get_persons() {
    return persons;
}
