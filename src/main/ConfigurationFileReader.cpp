#include <fstream>
#include <sstream>
#include <vector>

#include "ConfigurationFileReader.h"
#include "Feature.h"
#include "WantedPersonAlert.h"
#include "Resident.h"
#include "Foreigner.h"

#define SEPARATOR ','

std::vector<std::string> ConfigurationFileReader::split_line_into_tokens(std::string& line) {
    std::vector<std::string> result;

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, SEPARATOR)) {
        result.push_back(cell);
    }
    return result;
}

void ConfigurationFileReader::load_alerts(const std::string& alerts_file_path, Spawnables& alerts) {
    std::ifstream ifs(alerts_file_path);
    std::string line;

    // Get header
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {

        std::list<Feature*> wanted_person_features;

        std::stringstream ss(line);
        std::string feature_str;

        std::getline(ss, feature_str, SEPARATOR);
        int timestamp = stoi(feature_str);

        while (std::getline(ss, feature_str, SEPARATOR))  {
            Feature* feature = new Feature(feature_str);
            wanted_person_features.push_back(feature);
        }

        alerts.push_spawnable(timestamp, new WantedPersonAlert(wanted_person_features));
    }
}

void ConfigurationFileReader::load_fugitives_ids(std::list<std::string>& fugitives_ids) {
    std::ifstream ifs("../resources/fugitives.txt");
    std::string fugitive_id;

    // Get header
    std::getline(ifs, fugitive_id);
    while (std::getline(ifs, fugitive_id)) {
        fugitives_ids.emplace_back(fugitive_id);
    }
}

enum PEOPLE_FIELDS {
    timestamp = 0,
    resident = 1,
    id = 2,
    name = 3,
    last_name = 4,
    features_start = 5
};

std::list<Feature*> ConfigurationFileReader::extract_features(std::vector<std::string>& raw_features) {
    std::list<Feature*> l;
    for (auto const &i : raw_features) l.push_back(new Feature(i));
    return l;
}

void ConfigurationFileReader::load_persons(const std::string& people_file_path, Spawnables& persons) {
    // TODO add exception handling
    std::ifstream ifs(people_file_path);
    std::string line;

    // Get header
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        std::vector<std::string> tokenized_line = split_line_into_tokens(line);

        int timestamp = stoi(tokenized_line[PEOPLE_FIELDS::timestamp]);
        bool resident = stoi(tokenized_line[PEOPLE_FIELDS::resident]) == 1;
        unsigned int id = (unsigned int) stoi(tokenized_line[PEOPLE_FIELDS::id]);
        std::string name = tokenized_line[PEOPLE_FIELDS::name];
        std::string last_name = tokenized_line[PEOPLE_FIELDS::last_name];
        std::vector<std::string> raw_features(tokenized_line.begin() + PEOPLE_FIELDS::features_start, tokenized_line.end());
        std::list<Feature*> person_features = extract_features(raw_features);

        if (resident) {
            persons.push_spawnable(timestamp, new Resident(id, person_features));
        } else {
            persons.push_spawnable(timestamp, new Foreigner(Passport(), person_features));
        }
    }
}