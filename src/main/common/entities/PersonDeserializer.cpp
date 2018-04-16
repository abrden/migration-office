#include "PersonDeserializer.h"
#include "Resident.h"
#include "Foreigner.h"

#include <fstream>
#include <sstream>
#include <vector>

const static char SEPARATOR = ',';

enum PEOPLE_FIELDS {
    person_resident,
    person_id,
    person_features_start
};

Person* PersonDeserializer::deserialize(std::string& serialized_person) {
    std::vector<std::string> tokenized_line;

    std::stringstream lineStream(serialized_person);
    std::string cell;

    while (std::getline(lineStream, cell, SEPARATOR)) {
        tokenized_line.push_back(cell);
    }

    bool resident = stoi(tokenized_line[PEOPLE_FIELDS::person_resident]) == 1;

    std::vector<std::string> raw_features(tokenized_line.begin() + PEOPLE_FIELDS::person_features_start, tokenized_line.end());
    std::list<Feature*> features;
    for (auto const &i : raw_features) features.push_back(new Feature(i));

    if (resident) {
        unsigned int id = (unsigned int) stoi(tokenized_line[PEOPLE_FIELDS::person_id]);
        return new Resident(id, features);
    } else {
        std::string passport_id = tokenized_line[PEOPLE_FIELDS::person_id];
        return new Foreigner(passport_id, features);
    }
}