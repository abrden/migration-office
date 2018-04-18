#include "PersonDeserializer.h"
#include "Resident.h"
#include "Foreigner.h"
#include "ConfigurationFileReader.h"

#include <fstream>
#include <sstream>
#include <vector>

enum PEOPLE_FIELDS {
    is_resident,
    id,
    passport_id,
    features_start
};

Person* PersonDeserializer::deserialize(std::string& serialized_person) {
    ConfigurationFileReader fr;

    std::vector<std::string> tokenized_line = fr.split_line_into_tokens(serialized_person);

    bool resident = stoi(tokenized_line[PEOPLE_FIELDS::is_resident]) == 1;

    std::vector<std::string> raw_features(tokenized_line.begin() + PEOPLE_FIELDS::features_start, tokenized_line.end());
    std::list<Feature*> features = fr.extract_features(raw_features);

    if (resident) {
        unsigned int id = (unsigned int) stoi(tokenized_line[PEOPLE_FIELDS::id]);
        return new Resident(id, features);
    } else {
        std::string passport_id = tokenized_line[PEOPLE_FIELDS::passport_id];
        return new Foreigner(passport_id, features);
    }
}