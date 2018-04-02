#include "PersonsGenerator.h"
#include "Resident.h"
#include "Foreigner.h"

#include <fstream>
#include <sstream>
#include <iostream>

enum Fields {
    timestamp = 0,
    resident = 1,
    id = 2,
    name = 3,
    last_name = 4,
    features_start = 5
};

std::vector<std::string> split_line_into_tokens(std::string &line) {
    std::vector<std::string> result;

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }
    return result;
}

std::list<Feature*> extract_features(std::vector<std::string> raw_features) {
    std::list<Feature*> l;
    for (auto const &i : raw_features) l.push_back(new Feature(i));
    return l;
}

PersonsGenerator::PersonsGenerator(const std::string& persons_file_path) {
    std::ifstream ifs(persons_file_path);
    std::string line;

    // Get header
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        std::vector<std::string> tokenized_line = split_line_into_tokens(line);

        int timestamp = stoi(tokenized_line[Fields::timestamp]);
        bool resident = stoi(tokenized_line[Fields::resident]) == 1;
        unsigned int id = (unsigned int) stoi(tokenized_line[Fields::id]);
        std::string name = tokenized_line[Fields::name];
        std::string last_name = tokenized_line[Fields::last_name];
        std::vector<std::string> raw_features(tokenized_line.begin() + Fields::features_start, tokenized_line.end());
        std::list<Feature*> person_features = extract_features(raw_features);

        if (resident) {
            persons.push_spawnable(timestamp, new Resident(id, person_features));
        } else {
            persons.push_spawnable(timestamp, new Foreigner(Passport(), person_features));
        }
    }
}

Spawnables& PersonsGenerator::get_persons() {
    return persons;
}
